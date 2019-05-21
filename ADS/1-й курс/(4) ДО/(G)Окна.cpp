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

struct addon {
	int l;
	int r;
	int x;
	bool type;
	addon() {}
	addon(int a, int rr, int xx, bool t) {
		l = a; r = rr; x = xx; type = t;
	}
};

bool operator < (addon const& a, addon const& b) {
	return (a.x < b.x || (a.x == b.x && a.type && !b.type));
}

vector <addon> query;
int tree[4 * 400000 + 8];
int dt[4 * 400000 + 8];
int o = 400000 + 2;

int ans = 0, xAns = 0, yAns = 0;

inline int getval(int v) {
	return tree[v] + dt[v];
}

inline void push(int v) {
	tree[v] += dt[v];
	dt[(v << 1)] += dt[v];
	dt[(v << 1) + 1] += dt[v];
	dt[v] = 0;
}

void add(int v, int l, int r, int from, int to, int d) {
	if (r <= from || l >= to)
		return;
	if (from <= l && r <= to) {
		dt[v] += d;
		return;
	}
	int m = ((l + r) >> 1);
	push(v);
	add((v << 1), l, m, from, to, d);
	add((v << 1) + 1, m, r, from, to, d);
	tree[v] = max(getval(v << 1), getval((v << 1) + 1));
}

void getPoint(int v, int l, int r, int &y, bool isGet) {
	if (isGet) {
		return;
	}
	if (r - l == 1) {
		y = l;
		isGet = true;
		return;
	}
	push(v);
	int m = ((l + r) >> 1);
	if (getval(v << 1) == tree[v]) {
		getPoint((v << 1), l, m, y, isGet);
	}
	else {
		getPoint((v << 1) + 1, m, r, y, isGet);
	}
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("sparse.in", "r", stdin);
	freopen("sparse.out", "w", stdout);
	#endif*/

	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		x1 += 2e5 + 1;
		y1 += 2e5 + 1;
		x2 += 2e5 + 1;
		y2 += 2e5 + 1;
		query.push_back(addon(y1, y2, x1, true));
		query.push_back(addon(y1, y2, x2, false));
	}
	sort(query.begin(), query.end());
	for (int i = 0; i < query.size(); i++) {
		if (query[i].type) {
			add(1, 1, o, query[i].l, query[i].r + 1, 1);
			int nowMax = getval(1);
			if (ans < nowMax) {
				ans = nowMax;
				xAns = query[i].x;
				getPoint(1, 1, o, yAns, false);
			}
		}
		else {
			add(1, 1, o, query[i].l, query[i].r + 1, -1);
		}	
	}

	xAns -= (2e5 + 1);
	yAns -= (2e5 + 1);
	printf("%d\n%d %d", ans, xAns, yAns);
	return 0;
}