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
	int start, end, x = -1, y = -1;
	LL capacity, flow = 0;
	bool hasReversed = true;
	Edge* reversed = nullptr;

	Edge(int s, int e, LL c)
		: start(s), end(e), capacity(c) {
	}

	Edge(int s, int e, LL c, int x, int y, bool hasRev)
		: start(s), end(e), capacity(c), x(x), y(y), hasReversed(hasRev) {
	}
};

int n, m, s, t, MAX_N = 105, MAX_M = 105;
vector<LL> d;
vector<int> pointer;
vector<vector<Edge*>> edges;
vector<vector<char>> kingdom;
vector<int> markedVertexes;
LL maxFlow = 0;

void addEdge(int start, int end, LL capacity) {
	edges[start].push_back(new Edge(start, end, capacity));
	edges[end].push_back(new Edge(end, start, 0));
	edges[end].back()->reversed = edges[start].back();
	edges[start].back()->reversed = edges[end].back();
}

void addOrEdge(int start, int end, LL capacity, int x, int y, bool hasRev) {
	edges[start].push_back(new Edge(start, end, capacity, x, y, hasRev));
}

bool bfs() {
	queue<int> q;
	q.push(s);
	d.assign(MAX_N * MAX_M, -1);
	d[s] = 0;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (Edge* to : edges[v]) {
			if (d[to->end] == -1 && to->flow < to->capacity) {
				q.push(to->end);
				d[to->end] = d[v] + 1;
			}
		}
	}
	return d[t] != -1;
}

LL dfs(int v, LL flow) {
	if (v == t) {
		return flow;
	}
	for (int i = pointer[v]; i < edges[v].size(); ++i) {
		Edge* to = edges[v][i];
		if (to->flow < to->capacity && d[to->end] == d[v] + 1) {
			LL delta = dfs(to->end, min(flow, to->capacity - to->flow));
			if (delta > 0) {
				to->flow += delta;
				if (to->hasReversed) {
					to->reversed->flow -= delta;
				}
				return delta;
			}
		}
		pointer[v] = i + 1;
	}
	return 0;
}

LL dinic() {
	LL flow = 0;
	while (true) {
		if (!bfs()) {
			break;
		}
		pointer.assign(MAX_N * MAX_M, 0);
		while (true) {
			LL pushedFlow = dfs(s, INT_INF);
			flow += pushedFlow;
			if (pushedFlow == 0) {
				break;
			}
		}
	}
	return flow;
}

int getIndex(int x, int y) {
	return x * m + y;
}

int getDoubledIndex(int x, int y) {
	return getIndex(x, y) + m * n;
}

void marking(int v, vector<bool>& marked) {
	marked[v] = true;
	markedVertexes.push_back(v);
	for (Edge* edge : edges[v]) {
		if (!marked[edge->end]) {
			if (edge->flow < edge->capacity) {
				marking(edge->end, marked);
			}
		}
	}
}

void findMinCut() {
	vector<bool> marked(MAX_N * MAX_M, false);
	marking(s, marked);
	for (int v : markedVertexes) {
		for (Edge* edge : edges[v]) {
			if (!marked[edge->end] && edge->flow == 1) {
				kingdom[edge->x][edge->y] = '+';
				break;
			}
		}
	}
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	cin >> n >> m;
	kingdom.resize(n, vector<char>(m));
	edges.resize(MAX_N * MAX_M, vector<Edge*>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> kingdom[i][j];
			switch (kingdom[i][j]) {
			case '-':
				addOrEdge(getIndex(i, j), getDoubledIndex(i, j), INT_INF, i, j, false);
				break;
			case '.':
				addOrEdge(getIndex(i, j), getDoubledIndex(i, j), 1, i, j, false);
				break;
			case '#':
				addOrEdge(getIndex(i, j), getDoubledIndex(i, j), 0, i, j, false);
				break;
			case 'A':
				s = getDoubledIndex(i, j);
				break;
			case 'B':
				t = getIndex(i, j);
				break;
			default:
				break;
			}
		}
	}
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < m - 1; ++j) {
			addEdge(getDoubledIndex(i, j), getIndex(i + 1, j), INT_INF);
			addEdge(getDoubledIndex(i + 1, j), getIndex(i, j), INT_INF);
			addEdge(getDoubledIndex(i, j), getIndex(i, j + 1), INT_INF);
			addEdge(getDoubledIndex(i, j + 1), getIndex(i, j), INT_INF);
		}
	}
	for (int i = 0; i < n - 1; ++i) {
		addEdge(getDoubledIndex(i, m - 1), getIndex(i + 1, m - 1), INT_INF);
		addEdge(getDoubledIndex(i + 1, m - 1), getIndex(i, m - 1), INT_INF);
	}
	for (int j = 0; j < m - 1; ++j) {
		addEdge(getDoubledIndex(n - 1, j), getIndex(n - 1, j + 1), INT_INF);
		addEdge(getDoubledIndex(n - 1, j + 1), getIndex(n - 1, j), INT_INF);
	}
	maxFlow = dinic();
	findMinCut();
	if (maxFlow >= INT_INF) {
		cout << -1;
	}
	else {
		cout << maxFlow << endl;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cout << kingdom[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}