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

vector<int> mt, mtl;
vector<pair<int, int>> order; //cost - vertex
vector<bool> used;
vector<vector<int>> g;

bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.first > b.first;
}

bool try_kuhn(int v) {
	if (used[v])
		return false;
	used[v] = true;
	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		if (mt[to] == -1 || try_kuhn(mt[to])) {
			mt[to] = v;
			mtl[v] = to;
			return true;
		}
	}
	return false;
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("matching.in", "r", stdin);
	freopen("matching.out", "w", stdout);
	#endif
	int n;
	cin >> n;
	mt.assign(n, -1);
	mtl.assign(n, -1);
	g.resize(n);
	for (int i = 0; i < n; ++i) {
		int w;
		cin >> w;
		order.push_back(make_pair(w, i));
	}
	for (int i = 0; i < n; ++i) {
		int sz;
		cin >> sz;
		for (int j = 0; j < sz; ++j) {
			int v;
			cin >> v;
			g[i].push_back(v - 1);
		}
	}
	sort(order.begin(), order.end(), cmp);
	for (int i = 0; i < n; ++i) {
		int v = order[i].second;
		used.assign(n, false);
		try_kuhn(v);
	}
	for (int i = 0; i < n; ++i) {
		cout << mtl[i] + 1 << ' ';
	}
	return 0;
}