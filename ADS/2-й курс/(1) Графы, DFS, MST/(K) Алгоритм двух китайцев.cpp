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
const LL LINF = 1e18;

vector<vector<pair<int, int>>> graph; //from - to - number of edge
vector<vector<pair<int, int>>> backGraph;
vector<vector<int>> matrix;
vector<LL> minEdge;
vector<int> order, component;
vector<LL> weight;
vector<bool> used;
int componentNumber = 0;

void dfs(int v, bool onlyZero) {
	used[v] = true;
	for (int i = 0; i < graph[v].size(); ++i) {
		if (onlyZero) {
			if (!used[graph[v][i].first] && weight[graph[v][i].second] == 0) {
				dfs(graph[v][i].first, onlyZero);
			}
		}
		else {
			if (!used[graph[v][i].first]) {
				dfs(graph[v][i].first, onlyZero);
			}
		}
	}
}

void dfs1(int v) {
	used[v] = true;
	for (int i = 0; i < graph[v].size(); ++i) {
		if (!used[graph[v][i].first] && weight[graph[v][i].second] == 0) {
			dfs1(graph[v][i].first);
		}
	}
	order.push_back(v);
}

void dfs2(int v) {
	used[v] = true;
	for (int i = 0; i < backGraph[v].size(); ++i) {
		if (!used[backGraph[v][i].first] && weight[backGraph[v][i].second] == 0) {
			dfs2(backGraph[v][i].first);
		}
	}
	component[v] = componentNumber;
}

bool check(int start, bool onlyZero) {
	used.assign(graph.size(), false);
	dfs(start, onlyZero);
	for (int i = 0; i < graph.size(); ++i) {
		if (!used[i]) {
			return false;
		}
	}
	return true;
}

LL findMST(int start, int oldComp) {
	LL res = 0;
	minEdge.assign(backGraph.size(), LINF);
	for (int i = 0; i < backGraph.size(); ++i) {
		if (i == start) {
			continue;
		}
		for (int j = 0; j < backGraph[i].size(); ++j) {
			minEdge[i] = min(minEdge[i], weight[backGraph[i][j].second]);
		}
		for (int j = 0; j < backGraph[i].size(); ++j) {
			weight[backGraph[i][j].second] -= minEdge[i];
		}
		res += minEdge[i];
	}
	if (check(start, true)) {
		return res;
	}
	componentNumber = 0;
	order.clear();
	component.assign(graph.size(), -1);
	used.assign(graph.size(), false);
	for (int i = 0; i < graph.size(); ++i) {
		if (!used[i]) {
			dfs1(i);
		}
	}
	used.assign(graph.size(), false);
	for (int i = 0; i < graph.size(); ++i) {
		int v = order[graph.size() - i - 1];
		if (!used[v]) {
			dfs2(v);
			++componentNumber;
		}
	}
	matrix.assign(componentNumber, vector<int>(componentNumber, -1));
	for (int i = 0; i < graph.size(); ++i) {
		for (int j = 0; j < graph[i].size(); ++j) {
			int v = component[i];
			int u = component[graph[i][j].first];
			if (u != v) {
				if (matrix[v][u] == -1 || weight[matrix[v][u]] > weight[graph[i][j].second]) {
					matrix[v][u] = graph[i][j].second;
				}
			}
		}
	}
	graph.assign(componentNumber, vector<pair<int, int>>());
	backGraph.assign(componentNumber, vector<pair<int, int>>());
	for (int i = 0; i < componentNumber; ++i) {
		for (int j = 0; j < componentNumber; ++j) {
			if (matrix[i][j] != -1) {
				graph[i].push_back(make_pair(j, matrix[i][j]));
				backGraph[j].push_back(make_pair(i, matrix[i][j]));
			}
		}
	}
	if (componentNumber == oldComp) {
		return 1;
	}
	res += findMST(component[start], componentNumber);
	return res;
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	/*#else
	freopen("epsilon.in", "r", stdin);
	freopen("epsilon.out", "w", stdout);*/
	#endif
	int n, m;
	cin >> n >> m;
	graph.resize(n);
	backGraph.resize(n);
	weight.resize(m);
	for (int i = 0; i < m; ++i) {
		int x, y, w;
		cin >> x >> y >> w;
		--x, --y;
		graph[x].push_back(make_pair(y, i));
		backGraph[y].push_back(make_pair(x, i));
		weight[i] = w;
	}
	if (!check(0, false)) {
		cout << "NO";
		return 0;
	}
	cout << "YES" << endl;
	cout << findMST(0, -1);
	return 0;
}