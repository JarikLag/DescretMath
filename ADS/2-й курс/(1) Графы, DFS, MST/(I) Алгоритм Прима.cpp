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

inline double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("epsilon.in", "r", stdin);
	freopen("epsilon.out", "w", stdout);
	#endif*/
	int n;
	double ans = 0;
	cin >> n;
	vector<pair<double, double>> points(n);
	vector<double> minEdge(n, INF);
	vector<bool> used(n, false);
	for (int i = 0; i < n; ++i) {
		double x, y;
		cin >> x >> y;
		points[i] = make_pair(x, y);
	}
	minEdge[0] = 0;
	for (int i = 0; i < n; ++i) {
		int now = -1;
		for (int j = 0; j < n; ++j) {
			if (!used[j]) {
				if (now == -1 || minEdge[j] < minEdge[now]) {
					now = j;
				}
			}
		}
		used[now] = true;
		ans += minEdge[now];
		for (int j = 0; j < n; ++j) {
			minEdge[j] = min(dist(points[now].first, points[now].second, points[j].first, points[j].second), minEdge[j]);
		}
	}
	printf("%.10f", ans);
	return 0;
}