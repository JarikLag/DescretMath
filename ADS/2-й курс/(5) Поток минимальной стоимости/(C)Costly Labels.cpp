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
#include <variant>
using namespace std;

typedef long long LL;

const LL LONG_INF = 1e18;
const int INT_INF = 1e9 + 7;


vector<vector<int>> edges, costs, tree, table;
vector<vector<vector<int>>> dp;
vector<bool> used;
int n, k, p;

int matching(vector<vector<int>>& a, int n, int m) {
	vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);
	for (int i = 1; i <= n; ++i) {
		p[0] = i;
		int column = 0;
		vector<int> minv(m + 1, INT_INF);
		vector<bool> usedLocal(m + 1, false);
		do {
			usedLocal[column] = true;
			int row = p[column], delta = INT_INF, index;
			for (int j = 1; j <= m; ++j)
				if (!usedLocal[j]) {
					int cur = a[row][j] - u[row] - v[j];
					if (cur < minv[j]) {
						minv[j] = cur;
						way[j] = column;
					}
					if (minv[j] < delta) {
						delta = minv[j];
						index = j;
					}
				}
			for (int j = 0; j <= m; ++j)
				if (usedLocal[j]) {
					u[p[j]] += delta;
					v[j] -= delta;
				}
				else {
					minv[j] -= delta;
				}
			column = index;
		} while (p[column] != 0);
		do {
			int index = way[column];
			p[column] = p[index];
			column = index;
		} while (column);
	}
	return -v[0];
}

void buildTree(int v) {
	used[v] = true;
	for (int to : edges[v]) {
		if (!used[to]) {
			tree[v].push_back(to);
			buildTree(to);
		}
	}
	if (tree[v].empty()) {
		for (int color = 1; color <= k; ++color) {
			for (int parent = 0; parent <= k; ++parent) {
				dp[v][color][parent] = costs[v][color];
			}
		}
	}
}

int dfs(int v) {
	int minCost = INT_INF;
	for (int to : tree[v]) {
		dfs(to);
	}
	for (int parent_color = 1; parent_color <= k; ++parent_color) {
		for (int color = 1; color <= k; ++color) {
			if (tree[v].size() > 0) {
				dp[v][color][parent_color] = p + costs[v][color];
			}
			for (int child : tree[v]) {
				int child_cost = INT_INF;
				for (int child_color = 1; child_color <= k; ++child_color) {
					child_cost = min(child_cost, dp[child][child_color][color]);
				}
				dp[v][color][parent_color] += child_cost;
			}
			if (0 < tree[v].size() && tree[v].size() <= k - 1 ||
				(v == 1 && tree[v].size() <= k)) {
				for (int i = 0; i < tree[v].size(); ++i) {
					for (int child_color = 1; child_color <= k; ++child_color) {
						if (child_color == parent_color && v != 1) {
							table[i + 1][child_color] = INT_INF;
						}
						else {
							table[i + 1][child_color] = dp[tree[v][i]][child_color][color];
						}
					}
				}
				dp[v][color][parent_color] = min(dp[v][color][parent_color],
					matching(table, tree[v].size(), k) + costs[v][color]);
			}
			minCost = min(minCost, dp[v][color][parent_color]);
		}
	}
	return minCost;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#else
	/*freopen("assignment.in", "r", stdin);
	freopen("assignment.out", "w", stdout);*/
#endif
	cin >> n >> k >> p;
	edges.assign(n + 1, vector<int>());
	costs.assign(n + 1, vector<int>(k + 1, -1));
	dp.assign(n + 1, vector<vector<int>>(k + 1, vector<int>(k + 1)));
	tree.assign(n + 1, vector<int>());
	used.assign(n + 1, false);
	table.assign(n + 1, vector<int>(k + 1));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= k; ++j) {
			int a;
			cin >> a;
			costs[i][j] = a;
		}
	}
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	buildTree(1);
	dfs(1);
	int ans = INT_INF;
	for (int color = 1; color <= k; ++color) {
		ans = min(ans, dp[1][color][1]);
	}
	cout << ans;
	return 0;
}