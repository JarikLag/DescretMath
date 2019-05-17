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

struct edge {
	edge() : first(-1), second(-1), cost(INF) {}
	edge(int a, int b, int c) : first(a), second(b), cost(c) {}
	int first, second, cost;
};

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("fullham.in", "r", stdin);
	freopen("fullham.out", "w", stdout);
	#endif*/
	int n, m, k, s;
	cin >> n >> m >> k >> s;
	--s;
	vector<edge> edges;
	vector<vector<int>> d(k + 1, vector<int>(n, INF));
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		edges.push_back(edge(a, b, c));
	}
	d[0][s] = 0;
	for (int it = 1; it <= k; ++it) {
		for (int e = 0; e < m; ++e) {
			if (d[it - 1][edges[e].first] == INF) {
				continue;
			}
			else {
				d[it][edges[e].second] = min(d[it - 1][edges[e].first] + edges[e].cost, d[it][edges[e].second]);
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		if (d[k][i] == INF) {
			cout << -1;
		}
		else {
			cout << d[k][i];
		}
		cout << endl;
	}
	return 0;
}