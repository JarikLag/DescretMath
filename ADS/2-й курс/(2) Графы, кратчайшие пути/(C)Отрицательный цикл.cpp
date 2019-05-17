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

struct edge {
	edge() : first(-1), second(-1), cost(INF) {}
	edge(int a, int b, int c) : first(a), second(b), cost(c) {}
	int first, second, cost;
};

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("fullham.in", "r", stdin);
	freopen("fullham.out", "w", stdout);
	#endif*/
	int n;
	cin >> n;
	vector<edge> graph;
	vector<int> d(n, INF), p(n, -1), answer;
	d[0] = 0;
	int last;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int c;
			cin >> c;
			if (c != 100000) {
				graph.push_back(edge(i, j, c));
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		last = -1;
		for (int j = 0; j < graph.size(); ++j) {
			if (d[graph[j].second] > d[graph[j].first] + graph[j].cost) {
				d[graph[j].second] = max(-INF, d[graph[j].first] + graph[j].cost);
				p[graph[j].second] = graph[j].first;
				last = graph[j].second;
			}
		}
	}
	if (last == -1) {
		cout << "NO";
	}
	else {
		for (int i = 0; i < n; ++i) {
			last = p[last];
		}
		for (int cur = last;; cur = p[cur]) {
			answer.push_back(cur);
			if (cur == last && answer.size() > 1) {
				break;
			}
		}
		cout << "YES" << endl << answer.size() - 1 << endl;
		set<int> cpy;
		for (int i = answer.size() - 1; i >= 0; --i) {
			if (cpy.find(answer[i] + 1) == cpy.end()) {
				cpy.insert(answer[i] + 1);
				cout << answer[i] + 1 << ' ';
			}			
		}
	}
	return 0;
}