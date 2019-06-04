#pragma warning(disable : 4996)
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <ctime>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <sstream>
#include <stdio.h> 
#include <tuple>
#include <complex>
using namespace std;

typedef long long LL;
typedef complex<double> base;

const LL LONG_INF = 1e18;
const int INT_INF = 1e9 + 7;

void fft(vector<base>& a, bool invert) {
	int n = a.size();
	if (n == 1) {
		return;
	}
	vector<base> a0(n / 2), a1(n / 2);
	for (int i = 0, j = 0; i < n; i += 2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i + 1];
	}
	fft(a0, invert);
	fft(a1, invert);
	double ang = 2 * M_PI / n * (invert ? -1 : 1);
	base w(1), wn(cos(ang), sin(ang));
	for (int i = 0; i < n / 2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		if (invert) {
			a[i] /= 2, a[i + n / 2] /= 2;
		}
		w *= wn;
	}
}

void multiply(const vector<int>& a, const vector<int>& b, vector<int>& res) {
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while (n < max(a.size(), b.size())) {
		n <<= 1;
	}
	n <<= 1;
	fa.resize(n), fb.resize(n);
	fft(fa, false), fft(fb, false);
	for (int i = 0; i < n; ++i) {
		fa[i] *= fb[i];
	}
	fft(fa, true);
	res.resize(n);
	for (int i = 0; i < n; ++i) {
		res[i] = int(fa[i].real() + 0.5);
	}
}

void normalize(vector<int>& a) {
	int carry = 0;
	for (int i = 0; i < a.size(); ++i) {
		a[i] += carry;
		carry = a[i] / 10;
		a[i] %= 10;
	}
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#else
	/*freopen("assignment.in", "r", stdin);
	freopen("assignment.out", "w", stdout);*/
#endif
	string fst, snd;
	cin >> fst >> snd;
	bool negative = true, negF = false, negS = false;
	if (fst[0] == '-') {
		negF = true;
		fst[0] = '0';
	}
	if (snd[0] == '-') {
		negS = true;
		snd[0] = '0';
	}	
	if ((negF && negS) || (!negF && !negS)) {
		negative = false;
	}
	vector<int> a(fst.size()), b(snd.size());
	for (int i = 0; i < a.size(); ++i) {
		a[i] = fst[i] - '0';
	}
	for (int i = 0; i < b.size(); ++i) {
		b[i] = snd[i] - '0';
	}
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	vector<int> res;
	multiply(a, b, res);
	normalize(res);
	int ind = res.size() - 1;
	while (ind >= 0 && res[ind] == 0) {
		--ind;
	}
	if (ind == -1) {
		cout << 0;
		return 0;
	}
	if (negative) {
		cout << "-";
	}
	for (; ind >= 0; --ind) {
		cout << res[ind];
	}
	return 0;
}
