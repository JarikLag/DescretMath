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

const int MOD = 1e9 + 7;
	

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	int k, m;
	cin >> k >> m;
	vector<bool> weights(2000 + 1, false);
	vector<LL> pref(m + 1, 0), trees(m + 1, 0);	
	for (int i = 0; i < k; ++i) {
		int c;
		cin >> c;
		weights[c] = true;
	}
	pref[0] = 1;
	trees[0] = 1;
	for (int i = 1; i <= m; ++i) {
		LL sum = 0;
		for (int j = 0; j <= i; ++j) {
			if (weights[j]) {
				sum = (sum + pref[i - j]) % MOD;
			}
			else {
				continue;
			}
		}
		trees[i] = sum;
		for (int j = 0; j <= i; ++j) {
			pref[i] = (pref[i] + trees[j] * trees[i - j]) % MOD;
		}
	}
	for (int i = 1; i <= m; ++i) {
		cout << trees[i] << ' ';
	}
	return 0;
}