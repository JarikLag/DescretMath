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
vector<int> color, sum, last;
vector<bool> used;
vector<int> parent, time_in, time_out;
int timer = 0, l;

void dfs(int v, int p) {
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

void solve(int v) {
	used[v] = true;
	for (int to : tree[v]) {
		if (!used[to]) {
			solve(to);
			sum[v] += sum[to];
		}
	}
	if (last[color[v]] != -1) {
		sum[lca(v, last[color[v]])]--;
	}
	last[color[v]] = v;
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("mail.in", "r", stdin);
	freopen("mail.out", "w", stdout);
	#endif*/
	int n, root;
	scanf("%d", &n);
	l = ceil(log2(n));
	used.resize(n + 1, false);
	color.resize(n + 1);
	sum.resize(n + 1, 1);
	tree.resize(n + 1);
	last.resize(n + 1, -1);
	up.resize(n + 1, vector<int>(l + 1, 0));
	time_in.resize(n + 1, 0);
	time_out.resize(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		if (a == 0) {
			root = i;
		}
		tree[a].push_back(i);
		color[i] = b;
	}
	dfs(root, root);
	solve(root);
	for (int i = 1; i <= n; i++) {
		cout << sum[i] << ' ';
	}
	return 0;
}