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

vector<vector<int>> automat;
vector<vector<int>> graph;
vector<vector<int>> back_graph;
vector<vector<int>> useful_graph;
vector<bool> allow;
vector<bool> useful;
vector<bool> used;
vector<int> top_sort;
vector<int> color; //0-white, 1-grey, 2-black
vector<LL> paths;

void back_dfs(int v) {
	useful[v] = true;
	for (int i : back_graph[v]) {
		if (!useful[i])
			back_dfs(i);
	}
}

void useful_dfs(int v) {
	color[v] = 1;
	for (int i : useful_graph[v]) {
		if (color[i] == 0) {
			useful_dfs(i);
		}
		else if (color[i] == 1) {
			cout << -1;
			exit(0);
		}
	}
	color[v] = 2;
}

void dfs(int v) {
	used[v] = true;
	for (int i : graph[v]) {
		if (!used[i])
			dfs(i);
	}
	top_sort.push_back(v);
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("problem3.in", "r", stdin);
	freopen("problem3.out", "w", stdout);
	#endif
	int n, m, k;
	cin >> n >> m >> k;
	LL answer = 0, mod = 1e9 + 7;
	automat.resize(n + 1, vector<int>(30, 0));
	back_graph.resize(n + 1, vector<int>());
	useful_graph.resize(n + 1, vector<int>());
	graph.resize(n + 1, vector<int>());
	allow.resize(n + 1, false);
	useful.resize(n + 1, false);
	used.resize(n + 1, false);
	color.resize(n + 1, 0);
	paths.resize(n + 1, 0);

	for (int i = 0; i < k; i++) {
		int a;
		cin >> a;
		allow[a] = true;
		useful[a] = true;
	}
	for (int i = 0; i < m; i++) {
		int from, to;
		char c;
		cin >> from >> to >> c;
		automat[from][c - 'a'] = to;
		back_graph[to].push_back(from);
		graph[from].push_back(to);
	}

	for (int i = 1; i <= n; i++) { //find useful
		if (allow[i]) {
			back_dfs(i);
		}
	}
	if (!useful[1]) { //start is useless -> no words
		cout << answer;
		return 0;
	}
	for (int i = 1; i <= n; i++) { //create useful graph
		if (useful[i]) {
			for (int j : graph[i]) {
				if (useful[j])
					useful_graph[i].push_back(j);
			}
		}
	}
	useful_dfs(1); //check for cycle
	for (int i = 1; i <= n; i++) { //topological sort
		if (!used[i])
			dfs(i);
	}
	reverse(top_sort.begin(), top_sort.end());
	paths[1] = 1; //calculate paths
	for (int i : top_sort) {
		for (int j : back_graph[i]) {
			paths[i] = (paths[i] + paths[j]) % mod;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (allow[i]) {
			answer = (answer + paths[i]) % mod;
		}
	}
	cout << answer;
	return 0;
}