#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <ctime>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <sstream>
#include <stdio.h> 
#include <tuple>
using namespace std;

typedef long long LL;

const LL INF = 1e18;
const int INT_INF = 1e9 + 7;
const double EPS = 1e-5;

int n, w;
vector<LL> dist;
vector<bool> used;
vector<vector<LL>> graph;

struct Rectangle {
	Rectangle() {}

	Rectangle(LL x1, LL y1, LL x2, LL y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

	LL x1, x2, y1, y2;
};

vector<Rectangle> rectangles;

LL getDistance(Rectangle first, Rectangle second) {
	LL h, v, ans;
	if (first.x1 <= second.x1) {
		h = second.x1 - first.x2;
	}
	else {
		h = first.x1 - second.x2;
	}
	if (first.y1 <= second.y1) {
		v = second.y1 - first.y2;
	}
	else {
		v = first.y1 - second.y2;
	}
	ans = max(h, v);
	if (ans < 0) {
		ans = 0;
	}
	return ans;
}

void dijkstra() {
	dist[0] = 0;
	for (int i = 0; i < n + 2; ++i) {
		int v = -1;
		for (int j = 0; j < n + 2; ++j) {
			if (!used[j] && (v == -1 || dist[j] < dist[v])) {
				v = j;
			}
		}
		if (dist[v] == INF) {
			break;
		}
		used[v] = true;
		for (int j = 0; j < n + 2; ++j) {
			if (v != j) {
				if (dist[v] + graph[v][j] < dist[j]) {
					dist[j] = dist[v] + graph[v][j];
				}
			}
		}
	}
}


int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	cin >> n >> w;	
	graph.resize(n + 2, vector<LL>(n + 2));
	used.resize(10000, false);
	dist.resize(10000, INF);
	for (int i = 0; i < n; ++i) {
		LL x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		rectangles.push_back(Rectangle(x1, y1, x2, y2));
	}
	graph[0][n + 1] = w;
	graph[n + 1][0] = w;
	for (int i = 0; i < n; ++i) {
		Rectangle currentRectangle = rectangles[i];
		graph[0][i + 1] = graph[i + 1][0] = w - max(currentRectangle.y1, currentRectangle.y2);
		graph[n + 1][i + 1] = graph[i + 1][n + 1] = min(currentRectangle.y1, currentRectangle.y2);
		for (int j = 0; j < n; ++j) {
			if (i != j) {
				graph[i + 1][j + 1] = graph[j + 1][i + 1] = getDistance(currentRectangle, rectangles[j]);
			}
		}
	}
	dijkstra();
	if (dist[n + 1] == INF) {
		cout << 0;
	}
	else {
		cout << dist[n + 1];
	}
	return 0;
}