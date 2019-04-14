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

LL getElement(const vector<LL>& pol, const int ind) {
	if (ind >= pol.size()) {
		return 0;
	}
	else {
		return pol[ind];
	}
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	int n, m;
	cin >> n >> m;
	vector<LL> p(n + 1), q(m + 1);
	for (int i = 0; i < p.size(); ++i) {
		cin >> p[i];
	}
	for (int i = 0; i < q.size(); ++i) {
		cin >> q[i];
	}
	int maxi = max(m, n);
	cout << maxi << endl;
	for (int i = 0; i <= maxi; ++i) {
		LL cur = getElement(p, i) + getElement(q, i);
		cout << cur % MOD << ' ';
	}
	cout << endl;
	vector<LL> product(n + m + 1, 0);
	cout << n + m << endl;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			LL cur = getElement(p, i) * getElement(q, j);
			product[i + j] = (product[i + j] + cur) % MOD;
		}
	}
	for (int i = 0; i < product.size(); ++i) {
		cout << product[i] << ' ';
	}
	cout << endl;
	vector<LL> coefficient(1000, 0);
	for (int i = 0; i < 1000; ++i) {
		LL cur = getElement(p, i);
		for (int j = 1; j <= m; ++j) {
			if (j > i) {
				break;
			}
			cur = (cur - (coefficient[i - j] * getElement(q, j)) % MOD + MOD) % MOD;
		}
		coefficient[i] = cur;
		cout << coefficient[i] << ' ';
	}
	return 0;
}