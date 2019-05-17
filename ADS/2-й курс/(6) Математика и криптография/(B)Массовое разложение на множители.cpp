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

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#else
	/*freopen("assignment.in", "r", stdin);
	freopen("assignment.out", "w", stdout);*/
#endif
	int n;
	const int maxN = 1e6 + 5;
	scanf("%d", &n);
	vector<int> prime(maxN + 1);
	for (int i = 0; i < prime.size(); ++i) {
		prime[i] = i;
	}
	for (int i = 2; i <= maxN; ++i) {
		if (prime[i] == i) {
			if (i * 1ll * i <= maxN) {
				for (int j = i * i; j <= maxN; j += i)
					prime[j] = i;
			}
		}
	}
	vector<int> ans;
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		ans.clear();
		while (x != 1) {
			ans.push_back(prime[x]);
			x /= prime[x];
		}
		sort(ans.begin(), ans.end());
		for (int j = 0; j < ans.size(); ++j) {
			printf("%d ", ans[j]);
		}
		printf("\n");
	}
	return 0;
}