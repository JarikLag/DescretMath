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
	freopen("equivalence.in", "r", stdin);
	freopen("equivalence.out", "w", stdout);
	#endif
	int n1, m1, k1;
	cin >> n1 >> m1 >> k1;
	vector<vector<int>> automat1(n1 + 1, vector<int>(30, 0));
	vector<bool> allow1(n1 + 1, false);
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
	}

	int n2, m2, k2;
	cin >> n2 >> m2 >> k2;
	vector<vector<int>> automat2(n2 + 1, vector<int>(30, 0));
	vector<bool> allow2(n2 + 1, false);
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
	}
	vector<vector<bool>> used(max(n1, n2) + 1, vector<bool>(max(n1, n2) + 1, false));
	queue<pair<int, int>> q;
	q.push(make_pair(1, 1));
	while (!q.empty()) {
		pair<int, int> vertex = q.front();
		int v = vertex.first, u = vertex.second;
		q.pop();
		if (allow1[v] != allow2[u]) {
			cout << "NO";
			return 0;
		}
		used[v][u] = true;
		for (int c = 0; c < 30; c++) {
			if (!used[automat1[v][c]][automat2[u][c]]) {
				q.push(make_pair(automat1[v][c], automat2[u][c]));
			}
		}
	}
	cout << "YES";
	return 0;
}