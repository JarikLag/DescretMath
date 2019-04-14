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

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("problem1.in", "r", stdin);
	freopen("problem1.out", "w", stdout);
	#endif
	int n, m, k;
	string s;
	cin >> s;
	cin >> n >> m >> k;
	vector<vector<int>> graph(n + 1, vector<int>(30, 0));
	vector<bool> allow(n + 1, false);
	for (int i = 0; i < k; i++) {
		int a;
		cin >> a;
		allow[a] = true;
	}
	for (int i = 0; i < m; i++) {
		int from, to;
		char c;
		cin >> from >> to >> c;
		graph[from][c - 'a'] = to;
	}
	int pos = 1;
	for (int i = 0; i < s.length(); i++) {
		pos = graph[pos][s[i] - 'a'];
	}
	if (allow[pos]) {
		cout << "Accepts";
	}
	else {
		cout << "Rejects";
	}
	return 0;
}