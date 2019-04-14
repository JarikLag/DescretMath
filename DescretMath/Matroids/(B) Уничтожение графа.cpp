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
#include <bitset>
using namespace std;

typedef long long LL;

const LL INF = 1e18;

struct Edge {
	int begin = 0, end = 0, index = 0;
	LL weight = 0;
};
bool operator<(const Edge &a, const Edge &b) {
	return a.weight > b.weight;
}

vector<Edge> graph; //cost - begin - end
vector<int> parent;

int get(int x) {
	if (parent[x] != x) {
		parent[x] = get(parent[x]);
	}
	return parent[x];
}

void unite(int x, int y) {
	x = get(x);
	y = get(y);
	if (rand() % 2 == 1) {
		swap(x, y);
	}
	if (x != y) {
		parent[x] = y;
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("destroy.in", "r", stdin);
	freopen("destroy.out", "w", stdout);
	#endif
	int n, m;
	LL s, overallCost = 0, cost = 0;
	cin >> n >> m >> s;
	parent.resize(n + 1);
	for (int i = 0; i < m; ++i) {
		Edge e;
		cin >> e.begin >> e.end >> e.weight;
		e.index = i;
		overallCost += e.weight;
		graph.push_back(e);
	}
	sort(graph.begin(), graph.end());
	for (int i = 1; i <= n; ++i) {
		parent[i] = i;
	}
	vector<bool> tree(m, false), deleted(m, false);
	for (int i = 0; i < m; ++i) {
		int x = graph[i].begin, y = graph[i].end;
		LL c = graph[i].weight;
		if (get(x) != get(y)) {
			cost += c;
			unite(x, y);
			tree[i] = true;
		}
	}
	int index = m - 1;
	LL weight = 0;
	for (int i = m - 1; i >= 0; --i) {
		if (!tree[i]) {
			if (weight + graph[i].weight <= s) {
				weight += graph[i].weight;
				deleted[i] = true;
			}
			else {
				break;
			}
		}
	}
	vector<int> ans;
	for (int i = 0; i < tree.size(); ++i) {
		if (deleted[i]) {
			ans.push_back(graph[i].index);
		}
	}
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); ++i) {
		cout << ans[i] + 1 << ' ';
	}
	return 0;
}