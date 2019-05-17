#pragma warning(disable : 4996)
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
using namespace std;

typedef long long LL;

const LL LONG_INF = 1e18;
const int INT_INF = 1e9 + 7;

LL gcd(LL a, LL b, LL& x, LL& y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	LL x1, y1;
	LL d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

LL inversed(LL a, LL m) {
	LL x, y;
	LL g = gcd(a, m, x, y);
	if (g != 1) {
		assert("SHIT");
	}
	else {
		x = (x % m + m) % m;
		return x;
	}
}

LL chineseTheorem(vector<int> a, vector<int> p) {
	vector<vector<int>> r(2, vector<int>(2, 0));
	for (int i = 0; i < 2; ++i) {
		for (int j = i + 1; j < 2; ++j) {
			r[i][j] = inversed(p[i], p[j]);
		}
	}
	LL result = 0, mult = 1;
	vector<int> x(2, 0);
	for (int i = 0; i < 2; ++i) {
		x[i] = a[i];
		for (int j = 0; j < i; ++j) {
			x[i] = r[j][i] * (x[i] - x[j]);
			x[i] = x[i] % p[i];
			if (x[i] < 0) {
				x[i] += p[i];
			}
		}
		result += mult * x[i];
		mult *= p[i];
	}
	return result;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#else
	/*freopen("assignment.in", "r", stdin);
	freopen("assignment.out", "w", stdout);*/
#endif
	vector<int> a(2), p(2);
	cin >> a[0] >> a[1] >> p[0] >> p[1];
	cout << chineseTheorem(a, p);
	return 0;
}