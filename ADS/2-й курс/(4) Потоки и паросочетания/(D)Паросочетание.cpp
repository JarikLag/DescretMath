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

vector<int> mt;
vector<bool> used;
vector<vector<int> > g;

bool try_kuhn(int v) {
	if (used[v])
		return false;
	used[v] = true;
	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		if (mt[to] == -1 || try_kuhn(mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	int n, m;
	cin >> n >> m;
	g.resize(n + 1);
	mt.resize(m + 1, -1);
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		while (a != 0) {
			g[i].push_back(a);
			cin >> a;
		}
	}
	for (int i = 1; i <= n; i++) {
		used.assign(n + 1, false);
		try_kuhn(i);
	}
	vector<pair<int, int> > ans;
	for (int i = 1; i <= m; i++) {
		if (mt[i] != -1)
			ans.push_back(make_pair(mt[i], i));
	}
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i].first << ' ' << ans[i].second << endl;
	}
	return 0;
}