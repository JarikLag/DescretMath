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
		: start(s), end(e), capacity(c) {}
};

int n, m, s, t;
vector<int> d, pointer;
vector<Edge> edges;
vector<vector<int>> graph;

void addEdge(int start, int end, int capacity) {
	Edge e1(start, end, capacity),
		e2(end, start, capacity);
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

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	cin >> n >> m;
	s = 1, t = n;
	graph.resize(n + 1);
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		addEdge(a, b, c);
	}
	cout << dinic() << endl;
	for (int i = 0; i < edges.size(); i += 2) {
		cout << edges[i].flow << endl;
	}
	return 0;
}