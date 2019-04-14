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

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("automaton.in", "r", stdin);
	freopen("automaton.out", "w", stdout);
	#endif
	int n, m;
	int end = 99;
	string start;
	cin >> n >> start;
	vector<vector<vector<int>>> graph(100, vector<vector<int>>(100, vector<int>()));
	for (int i = 0; i < n; ++i) {
		string from, arrow, to;
		cin >> from >> arrow >> to;
		if (to.length() == 2) {
			graph[from[0] - 'A'][to[0] - 'a'].push_back(to[1] - 'A');
		}
		else {
			graph[from[0] - 'A'][to[0] - 'a'].push_back(end);
		}
	}
	cin >> m;
	for (int i = 0; i < m; ++i) {
		string s;
		cin >> s;
		set<int> now;
		now.insert(start[0] - 'A');
		bool okay = false;
		for (int j = 0; j < s.length(); ++j) {
			set<int> newnow;
			for (int nt : now) {
				for (int k = 0; k < graph[nt][s[j] - 'a'].size(); ++k) {
					newnow.insert(graph[nt][s[j] - 'a'][k]);
				}
			}
			now = newnow;
		}
		for (int nt : now) {
			if (nt == end) {
				okay = true;
				break;
			}
		}
		if (okay) {
			cout << "yes" << endl;
		}
		else {
			cout << "no" << endl;
		}
	}
	return 0;
}