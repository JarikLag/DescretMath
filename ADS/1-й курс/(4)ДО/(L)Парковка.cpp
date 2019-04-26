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
vector<int> tree(4 * 100000, 0);

void build(int v, int l, int r) {
	if (r - l == 1) {
		tree[v] = l;
		return;
	}
	int m = (l + r) >> 1;
	build(2 * v + 1, l, m);
	build(2 * v + 2, m, r);
	tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}

void modify(int v, int l, int r, int place, int val) {
	if (r - l == 1) {
		tree[v] = val;
		return;
	}
	int m = (l + r) >> 1;
	if (place < m) {
		modify(2 * v + 1, l, m, place, val);
	}
	else {
		modify(2 * v + 2, m, r, place, val);
	}
	tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}

int minimum(int v, int l, int r, int from, int to) {
	if (l >= to || r <= from)
		return INF;
	if (l >= from && r <= to) {
		return tree[v];
	}
	int m = (l + r) >> 1;
	return min(minimum(2 * v + 1, l, m, from, to), minimum(2 * v + 2, m, r, from, to));
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("parking.in", "r", stdin);
	freopen("parking.out", "w", stdout);
	#endif
	int n, m;
	cin >> n >> m;
	build(0, 0, n);
	for (int i = 0; i < m; i++) {
		int place;
		string s;
		cin >> s >> place;
		if (s == "exit") {
			modify(0, 0, n, place - 1, place - 1);
		}
		else {
			int mini = minimum(0, 0, n, place - 1, n), ans;
			if (mini == INF) {
				ans = minimum(0, 0, n, 0, place);
			}
			else {
				ans = mini;
			}
			modify(0, 0, n, ans, INF);
			cout << ans + 1 << endl;
		}
	}
	return 0;
}