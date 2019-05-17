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

vector<vector<int>> graph;
vector<int> answer, color; //0 - white, 1 - gray, 2 - black
vector<bool> used;

void dfs(int v) {
	used[v] = true;
	for (int i = 0; i < graph[v].size(); ++i) {
		if (!used[graph[v][i]]) {
			dfs(graph[v][i]);
		}
	}
	answer.push_back(v);
}

bool findCycle(int v) {
	color[v] = 1;
	for (int i = 0; i < graph[v].size(); ++i) {
		if (color[graph[v][i]] == 0) {
			if (findCycle(graph[v][i])) {
				return true;
			}
		}
		else if (color[graph[v][i]] == 1) {
			return true;
		}
	}
	color[v] = 2;
	return false;
}

void topSort(int n) {
	for (int i = 1; i <= n; ++i) {
		if (!used[i]) {
			dfs(i);
		}
	}
	reverse(answer.begin(), answer.end());
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
	graph.resize(n + 1);
	used.resize(n + 1, false);
	color.resize(n + 1, 0);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
	}
	for (int i = 1; i <= n; ++i) {
		if (findCycle(i)) {
			cout << "-1";
			return 0;
		}
	}
	topSort(n);
	for (int i = 0; i < n; ++i) {
		cout << answer[i] << ' ';
	}
	return 0;
}