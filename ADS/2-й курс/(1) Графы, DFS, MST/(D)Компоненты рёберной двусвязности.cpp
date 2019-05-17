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

const int INF = 1e9;

vector<vector<pair<int, int>>> graph;
vector<bool> used, isBridge;
vector<int> tin, up, bridges, color;
int timer = 0;

void dfs(int v, int p, int e) {
	++timer;
	used[v] = true;
	tin[v] = up[v] = timer;
	for (int i = 0; i < graph[v].size(); ++i) {
		int to = graph[v][i].first;
		if (to == p && e == graph[v][i].second) {
			continue;
		}
		if (used[to]) {
			up[v] = min(up[v], tin[to]);
		}
		else {
			dfs(to, v, graph[v][i].second);
			up[v] = min(up[v], up[to]);
		}
		if (tin[v] < up[to]) {
			bridges.push_back(graph[v][i].second);
		}
	}
}

void paint(int v, int cl) {
	color[v] = cl;
	for (int i = 0; i < graph[v].size(); ++i) {
		pair<int, int> to = graph[v][i];
		if (isBridge[to.second]) {
			continue;
		}
		else if (color[to.first] == 0) {
			paint(to.first, cl);
		}
	}
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("epsilon.in", "r", stdin);
	freopen("epsilon.out", "w", stdout);
	#endif*/
	int n, m;
	cin >> n >> m;
	graph.resize(n + 1);
	used.resize(n + 1, false);
	tin.resize(n + 1);
	up.resize(n + 1);
	for (int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(make_pair(b, i));
		graph[b].push_back(make_pair(a, i));
	}
	for (int i = 1; i <= n; ++i) {
		if (!used[i]) {
			dfs(i, -1, -1);
		}
	}
	used.resize(n + 1, false);
	isBridge.resize(m + 1, false);
	color.resize(n + 1, 0);
	sort(bridges.begin(), bridges.end());
	for (int i = 0; i < bridges.size(); ++i) {
		isBridge[bridges[i]] = true;
	}
	int maxColor = 0;
	for (int i = 1; i <= n; ++i) {
		if (color[i] == 0) {
			++maxColor;
			paint(i, maxColor);
		}
	}
	cout << maxColor << endl;
	for (int i = 1; i <= n; ++i) {
		cout << color[i] << ' ';
	}
	return 0;
}