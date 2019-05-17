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

int n, s, t, MAX_N = 105;
LL maxFlow = 0;
vector<vector<Edge*>> edges;
vector<set<int>> necessaryMatches;
vector<vector<char>> table;
vector<int> scores, necessaryPoints;
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

LL dinic() {
	while (true) {
		used.assign(MAX_N, false);
		LL pushedFlow = dfs(s, INT_INF);
		maxFlow += pushedFlow;
		if (pushedFlow == 0) {
			break;
		}
	}
	return maxFlow;
}

LL possiblePoints(int team) {
	LL count = 0;
	for (int i : necessaryMatches[team]) {
		if (i > team) {
			count += 3;
		}
	}
	return count;
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	cin >> n;
	s = 0, t = n + 1;
	edges.assign(MAX_N, vector<Edge*>());
	necessaryMatches.assign(MAX_N, set<int>());
	table.assign(MAX_N, vector<char>(MAX_N, '0'));
	scores.assign(MAX_N, 0);
	necessaryPoints.assign(MAX_N, 0);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> table[i][j];
			switch (table[i][j]) {
			case 'W':
				scores[i] += 3;
				break;
			case 'w':
				scores[i] += 2;
				break;
			case 'L':
				break;
			case 'l':
				scores[i] += 1;
				break;
			case '.':
				necessaryMatches[i].insert(j);
			default:
				break;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		int score;
		cin >> score;
		necessaryPoints[i] = max(0, score - scores[i]);
	}
	for (int i = 1; i <= n; ++i) {
		addEdge(s, i, possiblePoints(i));
	}
	for (int i = 1; i <= n; ++i) {
		addEdge(i, t, necessaryPoints[i]);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j : necessaryMatches[i]) {
			if (j > i) {
				addEdge(i, j, 3);
			}
		}
	}
	dinic();
	for (int i = 1; i <= n; ++i) {
		for (Edge* edge : edges[i]) {
			if (edge->end != t && edge->end != s && i < edge->end) {
				switch (edge->flow) {
				case 0:
					table[i][edge->end] = 'W';
					table[edge->end][i] = 'L';
					break;
				case 1:
					table[i][edge->end] = 'w';
					table[edge->end][i] = 'l';
					break;
				case 2:
					table[i][edge->end] = 'l';
					table[edge->end][i] = 'w';
					break;
				case 3:
					table[i][edge->end] = 'L';
					table[edge->end][i] = 'W';
					break;
				default:
					break;
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << table[i][j];
		}
		cout << endl;
	}
	return 0;
}