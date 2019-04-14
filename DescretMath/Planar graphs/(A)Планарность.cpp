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

vector<pair<int, int>> edges;
vector<vector<int>> bigraph;
vector<int> points;

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("planaritycheck.in", "r", stdin);
	freopen("planaritycheck.out", "w", stdout);
	#endif*/
	int n, m;
	cin >> n >> m;
	bigraph.resize(m);
	points.resize(n);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		edges.push_back(make_pair(a, b));
	}
	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		--a;
		points[a] = i;
	}
	for (int i = 0; i < m; ++i) {
		if (points[edges[i].first] > points[edges[i].second]) {
			swap(edges[i].first, edges[i].second);
		}
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			if (i != j) {
				if ((points[edges[i].first] < points[edges[j].first] && points[edges[i].second] < points[edges[j].second] && points[edges[j].first] < points[edges[i].second])
					|| (points[edges[i].first] > points[edges[j].first] && points[edges[i].second] > points[edges[j].second] && points[edges[j].second] > points[edges[i].first])) {
					bigraph[i].push_back(j);
					bigraph[j].push_back(i);
				}
			}
		}
	}
	vector<char> part(m, 0);
	vector<int> q(m);
	bool ok = true;
	for (int st = 0; st < m; ++st) {
		if (part[st] == 0) {
			int h = 0, t = 0;
			q[t++] = st;
			part[st] = 1;
			while (h < t) {
				int v = q[h++];
				for (int i = 0; i < bigraph[v].size(); ++i) {
					int to = bigraph[v][i];
					if (part[to] == 0) {
						part[to] = part[v] * (-1);
						q[t++] = to;
					}
					else {
						ok &= part[to] != part[v];
					}
				}
			}
		}
	}
	if (ok) {
		cout << "YES" << endl;
		for (int i = 0; i < n; ++i) {
			cout << 2 *  points[i] << ' ' << 0 << ' ';
		}
		cout << endl;
		for (int i = 0; i < m; ++i) {
			cout << (points[edges[i].first] + points[edges[i].second]) << ' ' << part[i] * (points[edges[i].second] - points[edges[i].first]) << endl;
		}
	}
	else {
		cout << "NO" << endl;
	}
	return 0;
}