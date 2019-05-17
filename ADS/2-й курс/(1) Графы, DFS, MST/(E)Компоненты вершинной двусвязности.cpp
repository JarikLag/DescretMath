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
vector<bool> used, isCutpoint;
vector<int> tin, up, color;
int timer = 0, maxColor = 0;

void dfs(int v, int p, int e) {
	++timer;
	used[v] = true;
	tin[v] = up[v] = timer;
	int child = 0;
	for (int i = 0; i < graph[v].size(); ++i) {
		int to = graph[v][i].first;
		if (to == p && graph[v][i].second == e) {
			continue;
		}
		if (used[to]) {
			up[v] = min(up[v], tin[to]);
		}
		else {
			dfs(to, v, graph[v][i].second);
			up[v] = min(up[v], up[to]);
			if (tin[v] <= up[to] && p != -1) {
				isCutpoint[v] = true;
			}
			child++;
		}
	}
	if (p == -1 && child > 1) {
		isCutpoint[v] = true;
	}
}

void paint(int v, int cl, int p, int e) {
	used[v] = true;
	for (int i = 0; i < graph[v].size(); ++i) {
		pair<int, int> to = graph[v][i];
		if (p == -1) {
			if (!used[to.first]) {
				++maxColor;
				color[to.second] = maxColor;
				paint(to.first, maxColor, v, to.second);
			}
		}
		else {
			if (to.first == p && to.second == e) {
				continue;
			}
			if (!used[to.first]) {
				if (tin[v] <= up[to.first]) {
					++maxColor;
					int newCl = maxColor;
					color[to.second] = newCl;
					paint(to.first, newCl, v, to.second);
				}
				else {
					color[to.second] = cl;
					paint(to.first, cl, v, to.second);
				}
			}
			else if (tin[to.first] < tin[v]) {
				color[to.second] = cl;
			}
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
	color.resize(m + 1, 0);
	isCutpoint.resize(n + 1, false);
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
	used.assign(n + 1, false);
	for (int i = 1; i <= n; ++i) {
		if (!used[i]) {
			paint(i, maxColor, -1, -1);
		}
	}
	cout << maxColor << endl;
	for (int i = 1; i <= m; ++i) {
		cout << color[i] << ' ';
	}
	return 0;
}