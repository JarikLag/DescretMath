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
using namespace std;

typedef long long LL;

const LL INF = 1e18;

vector<vector<int>> automat1;
vector<vector<int>> automat2;
vector<vector<int>> back_graph1;
vector<vector<int>> back_graph2;
vector<bool> allow1;
vector<bool> allow2;
vector<bool> useful1;
vector<bool> useful2;
vector<bool> used;

void back_dfs1(int v) {
	useful1[v] = true;
	for (int i : back_graph1[v]) {
		if (!useful1[i])
			back_dfs1(i);
	}
}

void back_dfs2(int v) {
	useful2[v] = true;
	for (int i : back_graph2[v]) {
		if (!useful2[i])
			back_dfs2(i);
	}
}

bool dfs(int u, int v) {
	used[u] = true;
	if (allow1[u] != allow2[v]) {
		return false;
	}
	bool result = true;
	for (int i = 0; i < automat1[u].size(); i++) {
		int t1 = automat1[u][i];
		int t2 = automat2[v][i];
		if (useful1[t1] != useful2[t2]) {
			return false;
		}
		if (!used[t1]) {
			result = result & dfs(t1, t2);
		}
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("isomorphism.in", "r", stdin);
	freopen("isomorphism.out", "w", stdout);
	#endif
	int n1, m1, k1;
	cin >> n1 >> m1 >> k1;
	automat1.resize(n1 + 1, vector<int>(30, 0));
	back_graph1.resize(n1 + 1, vector<int>());
	allow1.resize(n1 + 1, false);
	useful1.resize(n1 + 1, false);
	for (int i = 0; i < k1; i++) {
		int a;
		cin >> a;
		allow1[a] = true;
	}
	for (int i = 0; i < m1; i++) {
		int from, to;
		char c;
		cin >> from >> to >> c;
		automat1[from][c - 'a'] = to;
		back_graph1[to].push_back(from);
	}

	int n2, m2, k2;
	cin >> n2 >> m2 >> k2;
	automat2.resize(n2 + 1, vector<int>(30, 0));
	allow2.resize(n2 + 1, false);
	back_graph2.resize(n2 + 1, vector<int>());
	useful2.resize(n2 + 1, false);
	for (int i = 0; i < k2; i++) {
		int a;
		cin >> a;
		allow2[a] = true;
	}
	for (int i = 0; i < m2; i++) {
		int from, to;
		char c;
		cin >> from >> to >> c;
		automat2[from][c - 'a'] = to;
		back_graph2[to].push_back(from);
	}

	used.resize(max(n1, n2) + 1, false);
	for (int i = 1; i <= n1; i++) { //find useful1
		if (allow1[i]) {
			back_dfs1(i);
		}
	}
	for (int i = 1; i <= n2; i++) { //find useful2
		if (allow2[i]) {
			back_dfs2(i);
		}
	}
	if (dfs(1, 1)) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}
	return 0;
}