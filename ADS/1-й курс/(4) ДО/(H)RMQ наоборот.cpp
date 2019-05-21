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
using namespace std;

typedef long long LL;

LL INF = (1 << 31) - 1;
const LL MAXN = (LL)1e6 * 4;
LL a[MAXN];
vector<LL> tree(MAXN, INF), dt(MAXN, INF);

struct triple {
	int l, r, x;
	triple(int l, int r, int x) : l(l), r(r), x(x) {};
};

bool comp(triple a, triple b) {
	return a.x < b.x;
}

void push(int v, int l, int r) {
	if (dt[v] == INF)
		return;
	int m = (l + r) / 2;
	tree[2 * v] = dt[v];
	dt[2 * v] = dt[v];
	tree[2 * v + 1] = dt[v];
	dt[2 * v + 1] = dt[v];
	dt[v] = INF;
}

void modify(int v, int l, int r, int from, int to, LL value) {
	if (from >= r || to <= l)
		return;
	if (from <= l && to >= r) {
		tree[v] = value;
		dt[v] = value;
		return;
	}
	push(v, l, r);
	int m = (l + r) / 2;
	modify(2 * v, l, m, from, to, value);
	modify(2 * v + 1, m, r, from, to, value);
	tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}


void build(int v, int l, int r) {
	if (r - l == 1)
		tree[v] = a[l];
	else {
		int m = (l + r) / 2;
		build(2 * v + 1, l, m);
		build(2 * v + 2, m, r);
		tree[v] = min(tree[2 * v], tree[2 * v + 1]);
	}
}

LL minimum(int v, int l, int r, int from, int to) {
	if (from >= r || to <= l)
		return INF;
	push(v, l, r);
	if (from <= l && to >= r)
		return tree[v];
	int m = (r + l) / 2;
	return min(minimum(2 * v, l, m, from, to), minimum(2 * v + 1, m, r, from, to));
}

void buildOfAnswer(int v, int l, int r) {
	push(v, l, r);
	if (r - l == 1)
		a[l] = tree[v];
	else {
		int m = (l + r) / 2;
		buildOfAnswer(2 * v, l, m);
		buildOfAnswer(2 * v + 1, m, r);
	}
}
int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("rmq.in", "r", stdin);
	freopen("rmq.out", "w", stdout);
	#endif
	vector<triple> now;
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		LL l, r, x;
		cin >> l >> r >> x;
		l--;
		now.push_back(triple(l, r, x));
	}
	sort(now.begin(), now.end(), comp);
	for (int i = 0; i < now.size(); i++) {
		modify(1, 0, n, now[i].l, now[i].r, now[i].x);
	}
	for (int i = 0; i < now.size(); i++) {
		LL mini = minimum(1, 0, n, now[i].l, now[i].r);
		if (mini != now[i].x) {
			cout << "inconsistent" << endl;
			return 0;
		}
	}
	cout << "consistent" << endl;
	buildOfAnswer(1, 0, n);
	for (int i = 0; i < n; i++) {
		cout << a[i] << ' ';
	}
	return 0;
}