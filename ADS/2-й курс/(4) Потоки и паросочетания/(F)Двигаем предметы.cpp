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

struct Point {
	double x, y, speed;

	Point() : x(0), y(0), speed(0) 
	{}

	Point(double x, double y, double s) : x(x), y(y), speed(s)
	{}

	static double getDistance(const Point& a, const Point& b) {
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}

	static double getTime(const Point& from, const Point& to) {
		return getDistance(from, to) / from.speed;
	}
};

vector<vector<int>> graph;
vector<Point> objects, places;
vector<int> mt;
vector<bool> used;
int n;

bool try_kuhn(int v) {
	if (used[v]) {
		return false;
	}
	used[v] = true;
	for (int i = 0; i < graph[v].size(); ++i) {
		int to = graph[v][i];
		if (mt[to] == -1 || try_kuhn(mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}

bool checkTime(double time) {
	graph.assign(n, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (Point::getTime(objects[i], places[j]) <= time) {
				graph[i].push_back(j);
			}
		}
	}
	mt.assign(n, -1);
	for (int v = 0; v < n; ++v) {
		used.assign(n, false);
		try_kuhn(v);
	}
	for (int i = 0; i < n; ++i) {
		if (mt[i] == -1) {
			return false;
		}
	}
	return true;
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	cin >> n;
	for (int i = 0; i < n; ++i) {
		double a, b, c;
		cin >> a >> b >> c;
		objects.push_back(Point(a, b, c));
	}
	for (int i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		places.push_back(Point(a, b, 0));
	}
	double left = -1, right = 10001;
	while (right - left > EPS) {
		double time = (left + right) / 2;
		if (checkTime(time)) {
			right = time;
		}
		else {
			left = time;
		}
	}
	cout.precision(5);
	cout << fixed << left;
	return 0;
}