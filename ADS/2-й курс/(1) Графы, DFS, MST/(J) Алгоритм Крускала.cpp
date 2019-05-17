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

vector<pair<int, pair<int, int>>> graph; //cost - begin - end
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
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("epsilon.in", "r", stdin);
	freopen("epsilon.out", "w", stdout);
	#endif*/
	int n, m;
	cin >> n >> m;
	parent.resize(n + 1);
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		graph.push_back(make_pair(c, make_pair(a, b)));
	}
	sort(graph.begin(), graph.end());
	LL cost = 0;
	for (int i = 1; i <= n; i++) {
		parent[i] = i;
	}
	for (int i = 0; i < m; i++) {
		int x = graph[i].second.first, y = graph[i].second.second, c = graph[i].first;
		if (get(x) != get(y)) {
			cost += c;
			unite(x, y);
		}
	}
	cout << cost;
	return 0;
}