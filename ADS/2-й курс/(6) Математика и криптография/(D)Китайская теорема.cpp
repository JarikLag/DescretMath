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

LL inversed(LL a, LL m) {
	a = a % m;
	for (LL x = 1; x < m; x++)
		if ((a * x) % m == 1)
			return x;
}

LL chineseTheorem(vector<LL> a, vector<LL> p, int size) {
	vector<vector<LL>> r(size, vector<LL>(size, 0));
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			r[i][j] = inversed(p[i], p[j]);
		}
	}
	LL result = 0;
	LL mult_p = 1;
	vector<LL> x(size);
	for (int i = 0; i < 2; ++i) {
		x[i] = a[i];
		for (int j = 0; j < i; ++j) {
			x[i] = (x[i] - x[j]) * r[j][i];
			x[i] = x[i] % p[i];
			if (x[i] < 0) {
				x[i] += p[i];
			}
		}
		result += mult_p * x[i];
		mult_p *= p[i];
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
	vector<LL> a(2), p(2);
	cin >> a[0] >> a[1] >> p[0] >> p[1];
	cout << chineseTheorem(a, p, 2);
	return 0;
}