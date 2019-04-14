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
	int startIndex = -1, endIndex = -1;
	LL weight;
	Line() : start(), end(), weight(0) {}
	Line(const Point& a, const Point& b, int st, int end, LL w) : start(a), end(b), startIndex(st), endIndex(end), weight(w) {}

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

vector<vector<pair<int, LL>>> bigraph; //vertex - vertex - weight
vector<vector<int>> faces;

vector<Point> points;
vector<Line> edges;

vector<map<Point, int, Comparator> > planarGraph;
vector<int> edgeToFaces;
map<pair<int, int>, int> pointsToEdge;
map<pair<int, int>, bool> used;
vector<bool> usedEdges;

void dfs(int cur, int start, const Point from, vector<int>& vertices) {
	used[make_pair(start, cur)] = true;
	vertices.push_back(cur);
	auto it = planarGraph[cur].upper_bound(-from);
	if (it == planarGraph[cur].end()) {
		it = planarGraph[cur].begin();
	}
	if (used[make_pair(cur, it->second)]) {
		return;
	}
	dfs(it->second, cur, it->first, vertices);
	planarGraph[cur].erase(it);
	return;
}

int getReversedEdge(int ind) {
	if (ind % 2 == 0) {
		return ind + 1;
	}
	else {
		return ind - 1;
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	/*#else
	freopen("planaritycheck.in", "r", stdin);
	freopen("planaritycheck.out", "w", stdout);*/
	#endif
	int n, m, s, t, or_edges = 0;
	cin >> n >> m >> s >> t;
	--s, --t;
	planarGraph.resize(n);
	edgeToFaces.resize(2 * m);
	usedEdges.resize(2 * m);
	for (int i = 0; i < n; ++i) {
		double a, b;
		cin >> a >> b;
		points.push_back(Point(a, b));
	}
	for (int i = 0; i < m; ++i) {
		int a, b;
		LL w;
		cin >> a >> b >> w;
		--a, --b;
		Line cur1 = Line(points[a], points[b], a, b, w);
		Line cur2 = Line(points[b], points[a], b, a, w);
		edges.push_back(cur1);
		edges.push_back(cur2);
		pointsToEdge[make_pair(a, b)] = or_edges++;
		pointsToEdge[make_pair(b, a)] = or_edges++;
		planarGraph[a].insert(make_pair((cur1.end - cur1.start).getNormalized(), b));
		planarGraph[b].insert(make_pair((cur2.end - cur2.start).getNormalized(), a));
	}
	for (size_t i = 0; i < planarGraph.size(); ++i) {
		while (planarGraph[i].size() != 0) {
			vector<int> v, w;
			v.push_back(i);
			dfs(planarGraph[i].begin()->second, i, planarGraph[i].begin()->first, v);
			planarGraph[i].erase(planarGraph[i].begin());
			for (int j = 0; j < v.size() - 1; ++j) {
				w.push_back(pointsToEdge[make_pair(v[j], v[j + 1])]);
			}
			faces.push_back(w);
		}
	}
	for (int i = 0; i < faces.size(); ++i) {
		for (int j = 0; j < faces[i].size(); ++j) {
			edgeToFaces[faces[i][j]] = i;
		}
	}
	bigraph.resize(faces.size() + 1);
	int ignore = -1;
	for (int i = 0; i < faces.size(); ++i) {
		int ind_s = -1, ind_t = -1;
		for (int j = 0; j < faces[i].size(); ++j) {
			if (edges[faces[i][j]].startIndex == s) {
				ind_s = j;
			}
			if (edges[faces[i][j]].endIndex == t) {
				ind_t = j;
			}
		}
		if (ind_s != -1 && ind_t != -1) {
			vector<int> path;
			for (int j = ind_s; j != (ind_t + 1) % faces[i].size(); j = (j + 1) % faces[i].size()) {
				if (path.size() == 0) {
					path.push_back(faces[i][j]);
				}
				else {
					if (getReversedEdge(faces[i][j]) == path.back()) {
						path.pop_back();
					}
					else {
						path.push_back(faces[i][j]);
					}
				}
			}
			for (int j = 0; j < path.size(); ++j) {
				int e = getReversedEdge(path[j]);
				bigraph[bigraph.size() - 1].push_back(make_pair(edgeToFaces[e], edges[e].weight));
				bigraph[edgeToFaces[e]].push_back(make_pair(bigraph.size() - 1, edges[e].weight));
				usedEdges[e] = true;
				usedEdges[path[j]] = true;
			}
			ignore = i;
			break;
		}
	}
	for (int j = 0; j < edges.size(); ++j) {
		if (!usedEdges[j]) {
			int e = getReversedEdge(j);
			if (edgeToFaces[j] != edgeToFaces[e])
				bigraph[edgeToFaces[j]].push_back(make_pair(edgeToFaces[e], edges[j].weight));
		}
	}
	if (ignore == -1) {
		cout << 0;
		return 0;
	}
	vector<LL> d(bigraph.size(), INF);
	set<pair<LL, int>> q; //weight - vertex
	d[ignore] = 0;
	q.insert(make_pair(d[ignore], ignore));
	while (!q.empty()) {
		int v = q.begin()->second, cur_dist = q.begin()->first;
		q.erase(q.begin());
		if (cur_dist > d[v])
			continue;
		for (int i = 0; i < bigraph[v].size(); ++i) {
			int to = bigraph[v][i].first;
			LL len = bigraph[v][i].second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				q.insert(make_pair(d[to], to));
			}
		}
	}
	cout << d[bigraph.size() - 1];
	return 0;
}