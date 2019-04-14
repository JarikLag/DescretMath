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

const LL INF = 1e18;
const int INT_INF = 1e9 + 7;

const int MOD = 998244353;

LL gcd(LL a, LL b, LL& x, LL& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	LL x1, y1;
	LL d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

LL getInversed(LL a, LL m) {
	LL x, y;
	LL g = gcd(a, m, x, y);
	if (g != 1) {
		return 1;
	}
	else {
		x = (x % m + m) % m;
		return x;
	}
}

void print(const vector<LL>& q) {
	for (LL elem : q) {
		cout << elem << ' ';
	}
	cout << endl;
}

void summarize(const vector<LL>& coeff, const vector<vector<LL>>& polynoms, vector<LL>& ans) {
	for (int i = 0; i < ans.size(); ++i) {
		LL sum = 0;
		for (int j = 0; j < coeff.size(); ++j) {
			sum = (sum + (coeff[j] * polynoms[j][i]) % MOD) % MOD;
		}
		ans[i] = sum;
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	int n, m;
	cin >> n >> m;
	vector<LL> p(100 + 1);
	vector<vector<LL>> pPows(100 + 1, vector<LL>(100 + 1, 0));
	for (int i = 0; i <= n; ++i) {
		cin >> p[i];
	}
	pPows[0][0] = 1;
	pPows[1] = p;
	for (int i = 2; i <= 100; ++i) {
		for (int j = 0; j <= 100; ++j) {
			for (int k = 0; k <= 100; ++k) {
				if (k + j <= 100) {
					LL cur = (pPows[i - 1][k] * pPows[1][j]) % MOD;
					pPows[i][k + j] = ((pPows[i][k + j] + cur) % MOD + MOD) % MOD;
				}
				else {
					break;
				}
			}
		}
	}
	vector<LL> sqrtP(m, 0), expP(m, 0), lnP(m, 0);
	sqrtP[0] = 1;
	expP[0] = 1;
	lnP[1] = 1;
	//for sqrt
	for (int i = 0; i < m - 1; ++i) {
		LL numerator = sqrtP[i], denominator = 1;
		numerator = ((numerator * (1 - 2 * i)) % MOD + MOD) % MOD;
		numerator = ((numerator * (2 * i + 1)) % MOD + MOD) % MOD;
		numerator = ((numerator * (2 * i + 2)) % MOD + MOD) % MOD;
		numerator = ((numerator * (-1)) % MOD + MOD) % MOD;
		denominator = ((denominator * (-4 - 8 * i)) % MOD + MOD) % MOD;
		denominator = ((denominator * (i + 1)) % MOD + MOD) % MOD;
		denominator = ((denominator * (i + 1)) % MOD + MOD) % MOD;
		denominator = getInversed(denominator, MOD);
		sqrtP[i + 1] = ((numerator * denominator) % MOD + MOD) % MOD;
	}
	//for exp
	for (int i = 0; i < m - 1; ++i) {
		LL numerator = expP[i], denominator = 1;
		denominator = ((denominator * (i + 1)) % MOD + MOD) % MOD;
		denominator = getInversed(denominator, MOD);
		expP[i + 1] = ((numerator * denominator) % MOD + MOD) % MOD;
	}
	//for ln
	for (int i = 1; i < m - 1; ++i) {
		LL numerator = lnP[i], denominator = 1;
		numerator = ((numerator * (-1)) % MOD + MOD) % MOD;
		numerator = ((numerator * (i)) % MOD + MOD) % MOD;
		denominator = ((denominator * (i + 1)) % MOD + MOD) % MOD;
		denominator = getInversed(denominator, MOD);
		lnP[i + 1] = ((numerator * denominator) % MOD + MOD) % MOD;
	}
	vector<LL> sqrtAns(m), expAns(m), lnAns(m);
	summarize(sqrtP, pPows, sqrtAns);
	summarize(expP, pPows, expAns);
	summarize(lnP, pPows, lnAns);
	print(sqrtAns);
	print(expAns);
	print(lnAns);
	return 0;
}