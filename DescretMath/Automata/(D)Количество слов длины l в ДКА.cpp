#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <ctime>
#include <fstream>
#include <cassert>
using namespace std;

typedef long long LL;

const LL INF = 1e18;

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("problem4.in", "r", stdin);
	freopen("problem4.out", "w", stdout);
	#endif
	int n, m, k, l, mod = 1e9 + 7;
	cin >> n >> m >> k >> l;
	vector<vector<int>> graph(n + 1, vector<int>(30, 0));
	vector<vector<int>> dp(n + 1, vector<int>(l + 1, 0));
	vector<bool> allow(n + 1, false);	
	for (int i = 0; i < k; i++) {
		int a;
		cin >> a;
		allow[a] = true;
	}
	for (int i = 0; i < m; i++) {
		int from, to;
		char c;
		cin >> from >> to >> c;
		graph[from][c - 'a'] = to;
	}
	set<int> vertex1;
	vertex1.insert(1);
	dp[1][0] = 1;
	for (int i = 1; i <= l; i++) {
		set<int> vertex2;
		for (auto v = vertex1.begin(); v != vertex1.end(); v++) {
			for (int c = 0; c < 30; c++) {
				int u = graph[*v][c];
				if (u != 0) {
					dp[u][i] = (dp[*v][i - 1] + dp[u][i]) % mod;
					vertex2.insert(u);
				}
			}
		}
		swap(vertex1, vertex2);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (allow[i]) {
			ans = (ans + dp[i][l]) % mod;
		}
	}
	cout << ans;
	return 0;
}