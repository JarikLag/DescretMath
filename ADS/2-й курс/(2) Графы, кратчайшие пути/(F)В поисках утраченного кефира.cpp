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

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("fullham.in", "r", stdin);
	freopen("fullham.out", "w", stdout);
	#endif*/
	int n, m;
	scanf("%d %d", &n, &m);
	vector<vector<pair<int, LL>>> graph(n); //vertex - vertex - weight
	for (int i = 0; i < m; ++i) {
		int x, y;
		LL z;
		scanf("%d %d %lld", &x, &y, &z);
		--x, --y;
		graph[x].push_back(make_pair(y, z));
		graph[y].push_back(make_pair(x, z));
	}
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	--a, --b, --c;
	vector<LL> da(n, INF), db(n, INF), dc(n, INF);
	set<pair<LL, int>> q; //weight - vertex
	da[a] = 0;
	q.insert(make_pair(da[a], a));
	while (!q.empty()) {
		int v = q.begin()->second, cur_dist = q.begin()->first;
		q.erase(q.begin());
		if (cur_dist > da[v])
			continue;
		for (int i = 0; i < graph[v].size(); ++i) {
			int to = graph[v][i].first, len = graph[v][i].second;
			if (da[v] + len < da[to]) {
				da[to] = da[v] + len;
				q.insert(make_pair(da[to], to));
			}
		}
	}
	db[b] = 0;
	q.insert(make_pair(db[b], b));
	while (!q.empty()) {
		int v = q.begin()->second, cur_dist = q.begin()->first;
		q.erase(q.begin());
		if (cur_dist > db[v])
			continue;
		for (int i = 0; i < graph[v].size(); ++i) {
			int to = graph[v][i].first, len = graph[v][i].second;
			if (db[v] + len < db[to]) {
				db[to] = db[v] + len;
				q.insert(make_pair(db[to], to));
			}
		}
	}
	dc[c] = 0;
	q.insert(make_pair(dc[c], c));
	while (!q.empty()) {
		int v = q.begin()->second, cur_dist = q.begin()->first;
		q.erase(q.begin());
		if (cur_dist > dc[v])
			continue;
		for (int i = 0; i < graph[v].size(); ++i) {
			int to = graph[v][i].first, len = graph[v][i].second;
			if (dc[v] + len < dc[to]) {
				dc[to] = dc[v] + len;
				q.insert(make_pair(dc[to], to));
			}
		}
	}
	LL ans = min(da[b] + db[c], min(da[c] + dc[b], min(db[a] + da[c], min(db[c] + dc[a], min(dc[a] + da[b], dc[b] + db[a])))));
	if (ans >= INF)
		printf("-1");
	else
		printf("%lld", ans);
	return 0;
}