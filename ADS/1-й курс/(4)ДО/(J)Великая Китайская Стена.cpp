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

const int INF = 1e9;
vector<int> tree(4 * 1000000, 0);
vector<int> dt(4 * 1000000, -INF);

void push(int v, int l, int r) {
	if (r - l == 1) {
		dt[v] = -INF;
		return;
	}
	if (dt[v] == -INF)
		return;
	tree[2 * v + 1] = max(dt[v], tree[2 * v + 1]);
	tree[2 * v + 2] = max(dt[v], tree[2 * v + 2]);
	dt[2 * v + 1] = max(dt[v], dt[2 * v + 1]);
	dt[2 * v + 2] = max(dt[v], dt[2 * v + 2]);
	dt[v] = -INF;
}

void modify(int v, int l, int r, int from, int to, int val) {
	if (l >= to || r <= from)
		return;
	if (l >= from && r <= to) {
		tree[v] = max(tree[v], val);
		dt[v] = max(dt[v], val);
		return;
	}
	push(v, l, r);
	int m = (l + r) >> 1;
	modify(2 * v + 1, l, m, from, to, val);
	modify(2 * v + 2, m, r, from, to, val);
	tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}

pair<pair<int, int>, pair<int, int>> minimum(int v, int l, int r, int from, int to) {
	if (l >= to || r <= from)
		return make_pair(make_pair(INF, INF), make_pair(INF, INF));
	if (l >= from && r <= to) {
		return make_pair(make_pair(tree[v], v), make_pair(l, r));
	}
	push(v, l, r);
	int m = (l + r) >> 1;
	pair<pair<int, int>, pair<int, int>> leftPair = minimum(2 * v + 1, l, m, from, to), rightPair = minimum(2 * v + 2, m, r, from, to);
	if (leftPair.first.first < rightPair.first.first) {
		return leftPair;
	}
	else {
		return rightPair;
	}
}

void getIndex(int v, int l, int r, int val, int& pos, bool isGet) {
	if (isGet)
		return;
	if (r - l == 1) {
		if (tree[v] == val) {
			pos = l;
			isGet = true;
		}
		return;
	}
	push(v, l, r);
	int m = (l + r) >> 1;
	if (tree[2 * v + 1] == val)
		getIndex(2 * v + 1, l, m, val, pos, isGet);
	else 
		getIndex(2 * v + 2, m, r, val, pos, isGet);
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("parking.in", "r", stdin);
	freopen("parking.out", "w", stdout);
	#endif*/
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		string s;
		int a, b, c;
		cin >> s >> a >> b;
		if (s == "defend") {
			cin >> c;
			modify(0, 0, n, a - 1, b, c);
		} 
		else {
			pair<pair<int, int>, pair<int, int>> ansPair = minimum(0, 0, n, a - 1, b);
			int pos;
			getIndex(ansPair.first.second, ansPair.second.first, ansPair.second.second, ansPair.first.first, pos, false);
			cout << ansPair.first.first << ' ' << pos + 1 << endl;
		}
	}
	return 0;
}