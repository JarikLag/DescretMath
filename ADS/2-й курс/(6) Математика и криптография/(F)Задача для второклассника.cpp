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
#include <complex>
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

LL binaryMul(LL a, LL b, LL m) {
	if (b == 1) {
		return a;
	}
	if (b % 2 == 0) {
		LL t = binaryMul(a, b / 2, m);
		return (2 * t) % m;
	}
	return (binaryMul(a, b - 1, m) + a) % m;
}

LL binaryPow(LL a, LL b, LL m) {
	if (b == 0)
		return 1;
	if (b % 2 == 0) {
		LL t = binaryPow(a, b / 2, m);
		return binaryMul(t, t, m) % m;
	}
	return (binaryMul(binaryPow(a, b - 1, m), a, m)) % m;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#else
	/*freopen("assignment.in", "r", stdin);
	freopen("assignment.out", "w", stdout);*/
#endif
	int n, e, c;
	cin >> n >> e >> c;
	vector<int> divisors;
	for (int i = 2; i <= sqrt(n); ++i) {
		if (n % i == 0) {
			divisors.push_back(i);
			divisors.push_back(n / i);
		}
	}
	int mod = (divisors[0] - 1) * (divisors[1] - 1);
	int d = inversed(e, mod);
	cout << binaryPow(c, d, n);
	return 0;
}