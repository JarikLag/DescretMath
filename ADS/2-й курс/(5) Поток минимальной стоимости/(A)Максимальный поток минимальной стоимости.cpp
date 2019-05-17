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
	LL vertex, capacity, cost, flow, back;
};

void addEdge(vector<vector<Edge>>& g, LL a, LL b, LL u, LL c) {
	Edge r1 = { b, u, c, 0, g[b].size() };
	Edge r2 = { a, 0, -c, 0, g[a].size() };
	g[a].push_back(r1);
	g[b].push_back(r2);
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	freopen("mincost.in", "r", stdin);
	freopen("mincost.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	vector<vector<Edge> > g(n + 1);
	for (int i = 0; i < m; ++i) {
		LL a, b, c, d;
		cin >> a >> b >> c >> d;
		addEdge(g, a, b, c, d);
	}
	int s = 1, t = n;
	LL k = INF;
	LL flow = 0, cost = 0;
	while (flow < k) {
		vector<LL> id(n + 1, 0), d(n + 1, INF), p(n + 1), pEdge(n + 1);
		deque<LL> q;
		q.push_back(s);
		d[s] = 0;
		while (!q.empty()) {
			LL v = q.front();
			q.pop_front();
			id[v] = 2;
			for (int i = 0; i < g[v].size(); ++i) {
				Edge r = g[v][i];
				if (r.flow < r.capacity && d[v] + r.cost < d[r.vertex]) {
					d[r.vertex] = d[v] + r.cost;
					if (id[r.vertex] == 0) {
						q.push_back(r.vertex);
					}
					else if (id[r.vertex] == 2) {
						q.push_front(r.vertex);
					}
					id[r.vertex] = 1;
					p[r.vertex] = v;
					pEdge[r.vertex] = i;
				}
			}
		}
		if (d[t] == INF) {
			break;
		}
		LL addflow = k - flow;
		for (LL v = t; v != s; v = p[v]) {
			LL pv = p[v];  
			LL pr = pEdge[v];
			addflow = min(addflow, g[pv][pr].capacity - g[pv][pr].flow);
		}
		for (LL v = t; v != s; v = p[v]) {
			LL pv = p[v];  
			LL pr = pEdge[v], r = g[pv][pr].back;
			g[pv][pr].flow += addflow;
			g[v][r].flow -= addflow;
			cost += g[pv][pr].cost * addflow;
		}
		flow += addflow;
	}
	cout << cost;
	return 0;
}