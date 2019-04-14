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

vector<int> classes;
vector<unordered_set<int>> split;
vector<vector<int>> automat;
vector<vector<int>> graph;
vector<vector<int>> back_graph;
vector<vector<vector<int>>> inv;
vector<bool> term;
vector<bool> from_term;
vector<bool> from_start;

void back_dfs(int v) {
	from_term[v] = true;
	for (int i : back_graph[v]) {
		if (!from_term[i])
			back_dfs(i);
	}
}

void dfs(int v) {
	from_start[v] = true;
	for (int c = 0; c < 26; ++c) {
		if (automat[v][c] && !from_start[automat[v][c]])
			dfs(automat[v][c]);
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("fastminimization.in", "r", stdin);
	freopen("fastminimization.out", "w", stdout);
	#endif
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	const int magic_size = n + 1000;
	automat.resize(magic_size, vector<int>(27, 0));
	back_graph.resize(magic_size, vector<int>());
	inv.resize(magic_size, vector<vector<int>>(27));
	classes.resize(magic_size, -1);
	term.resize(magic_size, false);
	from_term.resize(magic_size, false);
	from_start.resize(magic_size, false);

	for (int i = 0; i < k; ++i) {
		int a;
		scanf("%d", &a);
		term[a] = true;
	}
	for (int i = 0; i < m; ++i) {
		int from, to;
		char c;
		scanf("%d %d %c\n", &from, &to, &c);
		automat[from][c - 'a'] = to;
		back_graph[to].push_back(from);
	}

	for (int i = 1; i <= n; ++i) {
		if (term[i]) {
			back_dfs(i);
		}
	}

	dfs(1);

	for (int i = 1; i <= n; ++i) {
		if (from_start[i] && from_term[i]) {
			for (int c = 0; c < 26; ++c) {
				int j = automat[i][c];
				if (j) {
					inv[j][c].push_back(i);
				}
			}
		}
	}
	unordered_set<int> R1, R2;
	for (int i = 1; i <= n; ++i) {
		if (from_start[i] && from_term[i]) {
			if (term[i]) {
				R1.insert(i);
				classes[i] = 0;
			}
			else {
				R2.insert(i);
				classes[i] = 1;
			}
		}
	}
	if (R1.size()) {
		split.push_back(R1);
	}
	if (R2.size()) {
		split.push_back(R2);
	}
	queue<pair<unordered_set<int>, int>> q;
	for (int i = 0; i < 26; ++i) {
		q.push(make_pair(R1, i));
		q.push(make_pair(R2, i));
	}

	while (!q.empty()) {
		unordered_map<int, unordered_set<int>> involved;
		for (int to : q.front().first) {
			for (int from : inv[to][q.front().second]) {
				involved[classes[from]].insert(from);
			}
		}
		q.pop();
		for (auto &it : involved) {
			if (split[it.first].size() > it.second.size()) {
				split.push_back(unordered_set<int>());
				for (int now : it.second) {
					split[it.first].erase(now);
					split.back().insert(now);
					classes[now] = int(split.size()) - 1;
				}
				for (int c = 0; c < 26; ++c) {
					q.push(make_pair(split.back(), c));
				}
			}
		}
	}

	int start = classes[1];
	if (start != -1) {
		for (int i = 1; i < magic_size; ++i) {
			if (classes[i] == start) {
				classes[i] = 0;
			}
			else if (classes[i] == 0) {
				classes[i] = start;
			}
		}
	}
	vector<vector<int>> new_automat(split.size(), vector<int>(27, -1));
	vector<bool> new_term(split.size(), false);
	int n_ans = new_automat.size(), k_ans = 0, m_ans = 0;
	for (int i = 0; i < magic_size; ++i) {
		if (classes[i] != -1) {
			if (term[i]) {
				k_ans += (!new_term[classes[i]]);
				new_term[classes[i]] = true;
			}
			for (int c = 0; c < 26; ++c) {
				if (automat[i][c] && classes[automat[i][c]] != -1 && new_automat[classes[i]][c] == -1) {
					m_ans++;
					new_automat[classes[i]][c] = classes[automat[i][c]];
				}
			}
		}
	}
	printf("%d %d %d\n", new_automat.size(), m_ans, k_ans);
	for (int i = 0; i < new_automat.size(); ++i) {
		if (new_term[i]) {
			printf("%d ", i + 1);
		}
	}
	printf("\n");
	for (int i = 0; i < new_automat.size(); ++i) {
		for (int c = 0; c < 26; ++c) {
			if (new_automat[i][c] != -1) {
				printf("%d %d %c\n", i + 1, new_automat[i][c] + 1, char(c + 'a'));
			}
		}
	}
	return 0;
}