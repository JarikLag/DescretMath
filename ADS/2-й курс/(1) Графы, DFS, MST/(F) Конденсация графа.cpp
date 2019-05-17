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

vector<vector<int>> graph, invertedGraph;
vector<bool> used;
vector<int> order, component;
int componentNumber = 0;

void dfs1(int v) {
	used[v] = true;
	for (int i = 0; i < graph[v].size(); ++i) {
		if (!used[graph[v][i]]) {
			dfs1(graph[v][i]);
		}
	}
	order.push_back(v);
}

void dfs2(int v) {
	used[v] = true;
	for (int i = 0; i < invertedGraph[v].size(); ++i) {
		if (!used[invertedGraph[v][i]]) {
			dfs2(invertedGraph[v][i]);
		}
	}
	component[v] = componentNumber;
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
	invertedGraph.resize(n + 1);
	component.resize(n + 1);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		invertedGraph[b].push_back(a);
	}
	used.resize(n + 1, false);
	for (int i = 1; i <= n; ++i) {
		if (!used[i]) {
			dfs1(i);
		}
	}
	used.assign(n + 1, false);
	for (int i = 0; i < n; ++i) {
		int v = order[n - i - 1];
		if (!used[v]) {
			componentNumber++;
			dfs2(v);
		}
	}
	int answer = 0;
	vector<vector<bool>> condEdges(componentNumber + 1, vector<bool>(componentNumber + 1, false));
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < graph[i].size(); ++j) {
			if (!condEdges[component[i]][component[graph[i][j]]] && component[i] != component[graph[i][j]]) {
				answer++;
				condEdges[component[i]][component[graph[i][j]]] = true;
			}
		}
	}
	cout << answer;
	return 0;
}