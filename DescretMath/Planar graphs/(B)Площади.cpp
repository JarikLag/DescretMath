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
const double EPS = 1e-8;

struct Point {
	double x, y;

	Point() : x(0), y(0) {}
	Point(double x, double y) : x(x), y(y) {}
	Point(const Point& other) : x(other.x), y(other.y) {}

	void swap(Point& other) {
		std::swap(x, other.x);
		std::swap(y, other.y);
	}

	Point& operator=(const Point& other) {
		if (&other != this) {
			Point(other).swap(*this);
		}
		return *this;
	}

	Point operator+(const Point& other) const { 
		return Point(x + other.x, y + other.y); 
	}

	Point operator-() const { 
		return Point(-x, -y); 
	}

	Point operator-(const Point& other) const { 
		return Point(x - other.x, y - other.y); 
	}

	double operator*(const Point& other) const { 
		return x * other.x + y * other.y; 
	}

	Point operator*(double t) const { 
		return Point(t * x, t * y); 
	}

	double length() const { 
		return sqrt(x * x + y * y); 
	}

	void normalize() { 
		double len = length(); 
		x = x / len;
		y = y / len;
	}

	Point getNormalized() const { 
		double len = length(); 
		return Point(x / len, y / len);
	}

	bool operator==(const Point& other) const { 
		return x == other.x && y == other.y; 
	}

	bool operator<(const Point& other) const {
		if (x == other.x) {
			return y < other.y;
		}
		else {
			return x < other.x;
		}
	}
};

struct Line {
	Point start, end;
	Line() : start(), end() {}
	Line(const Point& a, const Point& b) : start(a), end(b) {}

	bool isParallel(const Line& other) const {
		return ((end.x - start.x) * (other.end.y - other.start.y) 
			- (other.end.x - other.start.x) * (end.y - start.y) == 0);
	}

	Point getIntersection(const Line& other) const {
		double a = (end.x * start.y - start.x * end.y), 
			b = (other.end.x * other.start.y - other.start.x * other.end.y),
			del = (end.x - start.x) * (other.end.y - other.start.y) - (other.end.x - other.start.x) * (end.y - start.y);
		return Point((a * (other.end.x - other.start.x) - b * (end.x - start.x)) / del,
			(a * (other.end.y - other.start.y) - b * (end.y - start.y)) / del);
	}
};

struct Comparator {
	bool operator()(const Point& a, const Point& b) const {
		if (a.x == 1 && a.y == 0 
			&& b.x == 1 && b.y == 0) {
			return false;
		}
		if (a.x == 1 && a.y == 0) {
			return true;
		}
		if (b.x == 1 && b.y == 0) {
			return false;
		}
		if (a.y > 0 && b.y <= 0) {
			return false;
		}
		else if (a.y < 0 && b.y >= 0) {
			return true;
		}
		else if (a.y == 0) {
			return b.y > 0;
		}
		else {
			double cosa = a.x, cosb = b.x;
			if (a.y > 0) {
				return cosa < cosb;
			}
			else {
				return cosa > cosb;
			}
		}
	}
};

map<Point, int> points;
unordered_map<int, Point> coordinates;
vector<map<Point, int, Comparator>> graph;

double calculateArea(const vector<int>& vertices) {
	double res = 0;
	for (size_t i = 0; i < vertices.size(); ++i) {
		int p1, p2 = vertices[i];
		if (i == 0) {
			p1 = vertices.back();
		}
		else {
			p1 = vertices[i - 1];
		}
		res += (coordinates[p1].x - coordinates[p2].x) * (coordinates[p1].y + coordinates[p2].y);
	}
	return fabs(res) / 2;
}

double dfs(int cur, int start, const Point from, vector<int>& vertices) {
	if (start == cur) {
		double res = calculateArea(vertices);
		return res;
	}
	vertices.push_back(cur);
	auto it = graph[cur].upper_bound(from);
	if (it == graph[cur].end()) {
		it = graph[cur].begin();
	}
	double res = dfs(it->second, start, -it->first, vertices);
	graph[cur].erase(it);
	return res;
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	/*#else
	freopen("planaritycheck.in", "r", stdin);
	freopen("planaritycheck.out", "w", stdout);*/
	#endif
	cout.precision(5);
	int n;
	cin >> n;
	vector<Line> lines;
	for (int i = 0; i < n; i++) {
		Line l;
		cin >> l.start.x >> l.start.y >> l.end.x >> l.end.y;
		lines.push_back(l);
	}
	int currentPoint = 0;
	for (int i = 0; i < n; i++) {
		set<pair<Point, int>> intersections;
		for (int j = 0; j < n; j++) {
			if (i != j) {
				Line a = lines[i], b = lines[j];
				if (a.isParallel(b)) {
					continue;
				}
				Point intersectionPoint = a.getIntersection(b);
				if (points.find(intersectionPoint) == points.end()) {
					points.insert(make_pair(intersectionPoint, currentPoint));
					coordinates.insert(make_pair(currentPoint, intersectionPoint));
					graph.push_back(map<Point, int, Comparator>());
					++currentPoint;
				}
				intersections.insert(make_pair(intersectionPoint, points[intersectionPoint]));
			}
		}
		for (auto it = ++intersections.begin(); it != intersections.end(); ++it) {
			auto prev = --it;
			++it;
			graph[prev->second].insert(make_pair(((it->first - prev->first).getNormalized()), it->second));
			graph[it->second].insert(make_pair((prev->first - it->first).getNormalized(), prev->second));
		}
	}
	vector<double> result;
	for (size_t i = 0; i < graph.size(); ++i) {
		while (graph[i].size() != 0) {
			vector<int> v;
			v.push_back(i);
			double res = fabs(dfs(graph[i].begin()->second, i, -graph[i].begin()->first, v));
			graph[i].erase(graph[i].begin());
			if (res > EPS) {
				result.push_back(res);
			}
		}
	}
	sort(result.begin(), result.end());
	if (result.size() == 0) {
		cout << 0;
	}
	else {
		cout << result.size() - 1 << endl;
		for (size_t i = 0; i < result.size() - 1; ++i) {
			cout << fixed << result[i] << endl;
		}
	}
	return 0;
}