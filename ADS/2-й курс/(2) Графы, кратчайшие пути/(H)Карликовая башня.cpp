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

const LL INF = 1e18;

struct edge {
	int x, y;
	edge() {};
	edge(int x, int y) : x(x), y(y) {};
};

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("dwarf.in", "r", stdin);
	freopen("dwarf.out", "w", stdout);
	#endif
	int n, m;
	cin >> n >> m;
	vector<LL> d(n + 1);
	vector<bool> check(n + 1, true);
	vector<vector<edge>> edges(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> d[i];
	for (int i = 1; i <= m; i++) {
		int a, u, v;
		cin >> a >> u >> v;
		edges[u].push_back(edge(v, a));
		edges[v].push_back(edge(u, a));
	}
	queue<LL> q;
	for (int i = 1; i <= n; i++) {
		q.push(i);
	}
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		check[now] = false;
		for (int i = 0; i < edges[now].size(); i++) {
			edge tmp = edges[now][i];
			if (d[tmp.y] > d[tmp.x] + d[now]) {
				d[tmp.y] = d[tmp.x] + d[now];
				if (!check[tmp.y])
					q.push(tmp.y);
				check[tmp.y] = true;
			}
		}
	}
	cout << d[1];
	return 0;
}