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

const LL INF = LLONG_MAX;

struct edge {
	edge() : first(-1), second(-1), cost(INF) {}
	edge(int a, int b, LL c) : first(a), second(b), cost(c) {}
	int first, second;
	LL cost;
};

vector<bool> used;
vector<vector<int>> graph;

void dfs(int v) {
	used[v] = true;
	for (int i = 0; i < graph[v].size(); ++i) {
		if (!used[graph[v][i]]) {
			dfs(graph[v][i]);
		}
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("fullham.in", "r", stdin);
	freopen("fullham.out", "w", stdout);
	#endif
	int n, m, s;
	cin >> n >> m >> s;
	--s;
	vector<edge> edges;
	graph.resize(n, vector<int>());
	vector<LL> d(n, INF);
	vector<int> badass;
	used.resize(n, false);
	for (int i = 0; i < m; ++i) {
		int a, b;
		LL c;
		cin >> a >> b >> c;
		--a, --b;
		graph[a].push_back(b);
		edges.push_back(edge(a, b, c));
	}
	d[s] = 0;
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < edges.size(); ++i) {
			if (d[edges[i].first] == INF)
				continue;
			if (d[edges[i].second] > d[edges[i].first] + edges[i].cost) {
				d[edges[i].second] = d[edges[i].first] + edges[i].cost;
				if (k == n - 1) {
					badass.push_back(edges[i].second);
				}
			}
		}
	}
	for (int i = 0; i < badass.size(); ++i) {
		if (!used[badass[i]]) {
			dfs(badass[i]);
		}
	}
	for (int i = 0; i < n; ++i) {
		if (used[i]) {
			cout << '-';
		}
		else if (d[i] == INF) {
			cout << '*';
		}
		else {
			cout << d[i];
		}
		cout << endl;
	}
	return 0;
}