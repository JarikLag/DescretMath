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

int main() {
    /*#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #else
    freopen("fullham.in", "r", stdin);
    freopen("fullham.out", "w", stdout);
    #endif*/
	int n, m, s = 0;
	cin >> n >> m;
	vector<vector<pair<LL, int>>> graph(n); //vertex - vertex - weight
	for (int i = 0; i < m; ++i) {
		LL a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		graph[a].push_back(make_pair(b, c));
		graph[b].push_back(make_pair(a, c));
	}
	vector<LL> d(n, INF);
	priority_queue<pair<LL, int>> q; //weight - vertex
	d[s] = 0;
	q.push(make_pair(d[s], s));
	while (!q.empty()) {
		int v = q.top().second, cur_dist = q.top().first;
		q.pop();
		if (cur_dist > d[v])
			continue;
		for (int i = 0; i < graph[v].size(); ++i) {
			int to = graph[v][i].first, len = graph[v][i].second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				q.push(make_pair(-d[to], to));
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		cout << d[i] << ' ';
	}
	return 0;
}