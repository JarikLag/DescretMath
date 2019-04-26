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

const LL INF = 1e18;

vector<int> level;
vector<int> roots;
vector<vector<int>> graph;

int dfs(int v, int size, int &center, int p = -1) {
	int sum = 1;
	for (int x : graph[v])
		if (level[x] == -1 && x != p)
			sum += dfs(x, size, center, v);
	if (center == -1 && (2 * sum >= size || p == -1))
		center = v;
	return sum;
}

void build(int v, int size, int depth, int last) {
	int center = -1;
	dfs(v, size, center);
	level[center] = depth;
	roots[center] = last;
	for (int x : graph[center]) {
		if (level[x] == -1) {
			build(x, size / 2, depth + 1, center);
		}
	}
};

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("mail.in", "r", stdin);
	freopen("mail.out", "w", stdout);
	#endif*/
	int n;
	scanf("%d", &n);
	graph.resize(n + 1);
	roots.resize(n + 1, 0);
	level.resize(n + 1, -1);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	build(1, n, 0, 0);
	for (int i = 1; i <= n; i++) {
		printf("%d ", roots[i]);
	}
	return 0;
}