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

int n, m, s, t, k, MAX_N = 55, MAX_M = 205, MAX_D = 10005;
LL maxFlow = 0;
vector<vector<Edge*>> edges;
vector<int> from, to;
vector<bool> used;

void addEdge(int start, int end, LL capacity) {
	edges[start].push_back(new Edge(start, end, capacity));
	edges[end].push_back(new Edge(end, start, 0));
	edges[end].back()->reversed = edges[start].back();
	edges[start].back()->reversed = edges[end].back();
}

LL dfs(int v, LL flow) {
	if (v == t) {
		return flow;
	}
	used[v] = true;
	for (Edge* to : edges[v]) {
		if (!used[to->end] && to->flow < to->capacity) {
			LL delta = dfs(to->end, min(flow, to->capacity - to->flow));
			if (delta > 0) {
				to->flow += delta;
				to->reversed->flow -= delta;
				return delta;
			}
		}
	}
	return 0;
}

LL dinic(int to, LL last) {
	while (true) {
		for (int i = 0; i < to; ++i) {
			used[i] = false;
		}
		LL pushedFlow = dfs(s, last - maxFlow);
		maxFlow += pushedFlow;
		if (pushedFlow == 0 || maxFlow == last) {
			break;
		}
	}
	return maxFlow;
}

int getIndex(int x, int y) {
	return x * n + y;
}

int main() {
	freopen("bring.in", "r", stdin);
	freopen("bring.out", "w", stdout);
	cin >> n >> m >> k >> s >> t;
	--s, --t;
	used.assign(MAX_N * MAX_D, false);
	from.assign(MAX_M, -1);
	to.assign(MAX_M, -1);
	edges.assign(MAX_N * MAX_D, vector<Edge*>());
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		from[i] = --a;
		to[i] = --b;
	}
	int days = 1;
	LL count = 0;
	while (count != k) {
		for (int i = 0; i < n; ++i) {
			addEdge(getIndex(days - 1, i), getIndex(days, i), INT_INF);
		}
		for (int i = 0; i < m; ++i) {
			addEdge(getIndex(days - 1, from[i]), getIndex(days, to[i]), 1);
			addEdge(getIndex(days - 1, to[i]), getIndex(days, from[i]), 1);
		}
		int tmp = t;
		t = getIndex(days, t);
		maxFlow = 0;
		count += dinic(getIndex(days, n), k - count);
		++days;
		t = tmp;
	}
	cout << --days << endl;
	vector<int> ships(k + 5, s);
	vector<pair<int, int>> ans;
	int counter;
	for (int i = 1; i <= days; ++i) {
		counter = 0;
		ans.clear();
		for (int j = 1; j <= k; ++j) {
			for (Edge* edge : edges[ships[j]]) {
				if (edge->flow >= 1) {
					edge->flow -= 1;
					ships[j] = edge->end;
					if (edge->capacity != INT_INF) {
						++counter;
						ans.push_back(make_pair(j, edge->end % n + 1));
					}
					break;
				}
			}
		}
		cout << counter << ' ';
		for (pair<int, int> pr : ans) {
			cout << pr.first << ' ' << pr.second << ' ';
		}
		cout << endl;
	}
	return 0;
}