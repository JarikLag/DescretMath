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

const LL INF = 1e18 + 1;
vector<LL> tree(4 * 100000), a;
vector<LL> add(4 * 100000, 0), dSet(4 * 100000, INF);
vector<bool> isSet(4 * 100000, false);

void push(int v, int l, int r) {
	if (r - l == 1) {
		add[v] = 0;
		if (isSet[v]) {
			tree[v] = dSet[v];
			isSet[v] = false;
		}
		return;
	}
	if (add[v] != 0) {
		if (isSet[2 * v + 1]) {
			dSet[2 * v + 1] += add[v];
		}
		else {
			add[2 * v + 1] += add[v];
		}
		tree[2 * v + 1] += add[v];
		if (isSet[2 * v + 2])
			dSet[2 * v + 2] += add[v];
		else
			add[2 * v + 2] += add[v];
		tree[2 * v + 2] += add[v];
		add[v] = 0;
	}
	if (isSet[v]) {
		dSet[2 * v + 1] = dSet[v];
		tree[2 * v + 1] = dSet[v];
		isSet[2 * v + 1] = true;
		dSet[2 * v + 2] = dSet[v];
		tree[2 * v + 2] = dSet[v];
		isSet[2 * v + 2] = true;
		add[2 * v + 1] = add[2 * v + 2] = 0;
		isSet[v] = false;
	}
	tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}

void build(int v, int l, int r) {
	if (r - l == 1) {
		tree[v] = a[l];
	}
	else {
		int m = (l + r) / 2;
		build(2 * v + 1, l, m);
		build(2 * v + 2, m, r);
		tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
	}
}

LL getMin(int v, int l, int r, int from, int to) {
	push(v, l, r);
	if (l >= to || r <= from)
		return INF;
	if (l >= from && r <= to) {
		return tree[v];
	}
	else {
		int m = (l + r) / 2;
		return min(getMin(2 * v + 1, l, m, from, to),
			getMin(2 * v + 2, m, r, from, to));
	}
}

void setAll(int v, int l, int r, int from, int to, LL val) {
	push(v, l, r);
	if (l >= to || r <= from)
		return;
	if (l >= from && r <= to) {
		tree[v] = val;
		isSet[v] = true;
		dSet[v] = val;
		add[v] = 0;
	}
	else {
		int m = (l + r) / 2;
		setAll(2 * v + 1, l, m, from, to, val);
		setAll(2 * v + 2, m, r, from, to, val);
		push(v, l, r);
	}
}

void addAll(int v, int l, int r, int from, int to, LL val) {
	push(v, l, r);
	if (l >= to || r <= from)
		return;
	if (l >= from && r <= to) {
		tree[v] += val;
		add[v] = val;
	}
	else {
		push(v, l, r);
		int m = (l + r) / 2;
		addAll(2 * v + 1, l, m, from, to, val);
		addAll(2 * v + 2, m, r, from, to, val);
		push(v, l, r);
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("rmq2.in", "r", stdin);
	freopen("rmq2.out", "w", stdout);
	#endif
	
	int n;
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	build(0, 0, n);
	string s;
	while (cin >> s) {
		int x, y;
		LL v;
		cin >> x >> y;
		if (s == "min") {			
			cout << getMin(0, 0, n, x - 1, y) << endl;
		}
		else {
			cin >> v;
			if (s == "set") {
				setAll(0, 0, n, x - 1, y, v);
			}
			else {
				addAll(0, 0, n, x - 1, y, v);
			}
		}
	}
	return 0;
}