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

struct Edge {
	int start, end, capacity, flow = 0;
	Edge(int s, int e, int c)
		: start(s), end(e), capacity(c) {
	}
};

int n, m, s, t;
vector<int> d, pointer;
vector<Edge> edges;
vector<vector<int>> graph;
vector<bool> used;

void addEdge(int start, int end, int capacity) {
	Edge e1(start, end, capacity),
		e2(end, start, 0);
	graph[start].push_back(edges.size());
	edges.push_back(e1);
	graph[end].push_back(edges.size());
	edges.push_back(e2);
}

bool bfs() {
	queue<int> q;
	q.push(s);
	d.assign(n + 1, -1);
	d[s] = 0;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < graph[v].size(); ++i) {
			int ind = graph[v][i], to = edges[ind].end;
			if (d[to] == -1 && edges[ind].flow < edges[ind].capacity) {
				q.push(to);
				d[to] = d[v] + 1;
			}
		}
	}
	return d[t] != -1;
}

int dfs(int v, int flow) {
	if (!flow) {
		return 0;
	}
	if (v == t) {
		return flow;
	}
	for (; pointer[v] < graph[v].size(); ++pointer[v]) {
		int id = graph[v][pointer[v]],
			to = edges[id].end;
		if (d[to] != d[v] + 1) {
			continue;
		}
		int pushed = dfs(to, min(flow, edges[id].capacity - edges[id].flow));
		if (pushed) {
			edges[id].flow += pushed;
			edges[id ^ 1].flow -= pushed;
			return pushed;
		}
	}
	return 0;
}

int dinic() {
	int flow = 0;
	while (bfs()) {
		pointer.assign(n + 1, 0);
		while (int pushed = dfs(s, INT_INF)) {
			flow += pushed;
		}
	}
	return flow;
}

void findPath(int v, bool& found, vector<int>& path) {
	used[v] = true;
	path.push_back(v);
	if (v == t) {
		found = true;
		return;
	}
	for (int i = 0; i < graph[v].size(); ++i) {
		int id = graph[v][i],
			to = edges[id].end;
		if (!used[to] && edges[id].flow == 1) {
			edges[id].flow = 0;
			findPath(to, found, path);
			if (found) {
				return;
			}
		}
	}
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	cin >> n >> m >> s >> t;
	graph.resize(n + 1);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		addEdge(a, b, 1);
	}
	dinic();
	used.assign(n + 1, false);
	vector<int> path1, path2;
	bool found = false;
	findPath(s, found, path1);
	if (path1.size() > 0 && path1.back() == t) {
		found = false;
		used.assign(n + 1, false);
		findPath(s, found, path2);
		if (path2.size() > 0 && path2.back() == t) {
			cout << "YES\n";
			for (int i = 0; i < path1.size(); ++i) {
				cout << path1[i] << ' ';
			}
			cout << endl;
			for (int i = 0; i < path2.size(); ++i) {
				cout << path2[i] << ' ';
			}
		}
		else {
			cout << "NO";
		}
	}
	else {
		cout << "NO";
	}
	return 0;
}