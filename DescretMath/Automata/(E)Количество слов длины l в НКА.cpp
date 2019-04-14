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
	freopen("problem5.in", "r", stdin);
	freopen("problem5.out", "w", stdout);
	#endif
	int n, m, k, l, mod = 1e9 + 7;
	cin >> n >> m >> k >> l;
	vector<vector<int>> dp(101, vector<int>(l + 1, 0));
	vector<vector<vector<int>>> NFAgraph(n + 1, vector<vector<int>>(30, vector<int>()));
	vector<vector<int>> graph(101, vector<int>(30, 0));
	vector<bool> NFAallow(n + 1, false);
	vector<bool> allow(101, false);
	for (int i = 0; i < k; i++) {
		int a;
		cin >> a;
		NFAallow[a] = true;
	}
	for (int i = 0; i < m; i++) {
		int from, to;
		char c;
		cin >> from >> to >> c;
		NFAgraph[from][c - 'a'].push_back(to);
	}

	string base;
	for (int i = 0; i <= 101; i++) {
		base += '0';
	}
	set<int> initial;
	string mask = base;
	map<string, int> cond;
	queue<set<int>> q;
	int curInd = 2;
	initial.insert(1);
	mask[1] = '1';
	cond[mask] = 1;
	allow[1] = NFAallow[1];
	q.push(initial);
	set<int> newCond;
	while (!q.empty()) {
		set<int> current = q.front();
		q.pop();
		string curMask = base;
		for (int i : current) {
			curMask[i] = '1';
		}
		for (int symb = 0; symb < 30; symb++) {
			mask = base;
			newCond.clear();
			bool term = false;
			for (int v : current) {
				if (NFAgraph[v][symb].size() > 0) {
					newCond.insert(NFAgraph[v][symb].begin(), NFAgraph[v][symb].end());
					for (int a : NFAgraph[v][symb]) {
						mask[a] = '1';
						if (NFAallow[a]) {
							term = true;
						}
					}
				}
			}
			if (cond[mask] == 0) {
				cond[mask] = curInd;
				if (term) {
					allow[curInd] = true;
				}
				curInd++;
				q.push(newCond);
			}
			graph[cond[curMask]][symb] = cond[mask];
		}
	}

	set<int> vertex1;
	vertex1.insert(1);
	dp[1][0] = 1;
	for (int i = 1; i <= l; i++) {
		set<int> vertex2;
		for (auto v = vertex1.begin(); v != vertex1.end(); v++) {
			for (int c = 0; c < 30; c++) {
				int u = graph[*v][c];
				if (u != 0) {
					dp[u][i] = (dp[*v][i - 1] + dp[u][i]) % mod;
					vertex2.insert(u);
				}
			}
		}
		swap(vertex1, vertex2);
	}
	int ans = 0;
	for (int i = 1; i <= 100; i++) {
		if (allow[i]) {
			ans = (ans + dp[i][l]) % mod;
		}
	}
	cout << ans;
	return 0;
}