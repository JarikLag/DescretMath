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
vector<bool> used;
vector<int> tin, up;
set<int> cutpoints;
int timer = 0;

void dfs(int v, int p) {
	timer++;
	used[v] = true;	
	tin[v] = up[v] = timer;
	int child = 0;
	for (int i = 0; i < graph[v].size(); ++i) {
		int to = graph[v][i];
		if (to == p) {
			continue;
		}
		if (used[to]) {
			up[v] = min(up[v], tin[to]);
		}
		else {
			dfs(to, v);
			up[v] = min(up[v], up[to]);
			if (tin[v] <= up[to] && p != -1) {
				cutpoints.insert(v);
			}
			child++;
		}		
	}
	if (p == -1 && child > 1) {
		cutpoints.insert(v);
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
	graph.resize(n + 1);
	used.resize(n + 1, false);
	tin.resize(n + 1);
	up.resize(n + 1);
	for (int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	for (int i = 1; i <= n; ++i) {
		if (!used[i]) {
			dfs(i, -1);
		}
	}
	cout << cutpoints.size() << endl;
	for (auto i = cutpoints.begin(); i != cutpoints.end(); ++i) {
		cout << *i << ' ';
	}
	return 0;
}