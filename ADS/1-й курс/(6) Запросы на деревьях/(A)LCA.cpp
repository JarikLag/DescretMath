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
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef long long LL;

const LL INF = 1e18;

vector<vector<int>> tree, up;
vector<int> parent, time_in, time_out;
int timer = 0, l;

void dfs(int v, int p = 1) {
	time_in[v] = ++timer;
	up[v][0] = p;
	for (int i = 1; i <= l; i++) {
		up[v][i] = up[up[v][i - 1]][i - 1];
	}
	for (int to : tree[v]) {
		if (to != p) {
			dfs(to, v);
		}
	}
	time_out[v] = ++timer;
}

bool is_upper(int u, int v) {
	return time_in[u] <= time_in[v] && time_out[u] >= time_out[v];
}

int lca(int u, int v) {
	if (is_upper(u, v)) {
		return u;
	}
	if (is_upper(v, u)) {
		return v;
	}
	for (int i = l; i >= 0; i--) {
		if (!is_upper(up[u][i], v)) {
			u = up[u][i];
		}
	}
	return up[u][0];
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	/*freopen("fastminimization.in", "r", stdin);
	freopen("fastminimization.out", "w", stdout);*/
	#endif
	int n, m;
	cin >> n;
	l = ceil(log2(n));
	tree.resize(n + 1);
	up.resize(n + 1);
	parent.resize(n + 1);
	time_in.resize(n + 1);
	time_out.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		up[i].resize(l + 1);
	}
	for (int i = 2; i <= n; i++) {
		int x;
		cin >> x;
		parent[i] = x;
		tree[x].push_back(i);
	}
	dfs(1);
	cin >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		cout << lca(u, v) << endl;
	}
	return 0;
}