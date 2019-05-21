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

LL n, m, r;

struct matrix {
	LL arr[2][2];

	matrix() {
		arr[0][0] = arr[0][1] = arr[1][0] = arr[1][1] = 0;
	}

	matrix(int a, int b, int c, int d) {
		arr[0][0] = a;
		arr[0][1] = b;
		arr[1][0] = c;
		arr[1][1] = d;
	}

	matrix operator*(matrix& a) {
		matrix res;
		res.arr[0][0] = (this->arr[0][0] * a.arr[0][0] + this->arr[0][1] * a.arr[1][0]) % r;
		res.arr[0][1] = (this->arr[0][0] * a.arr[0][1] + this->arr[0][1] * a.arr[1][1]) % r;
		res.arr[1][0] = (this->arr[1][0] * a.arr[0][0] + this->arr[1][1] * a.arr[1][0]) % r;
		res.arr[1][1] = (this->arr[1][0] * a.arr[0][1] + this->arr[1][1] * a.arr[1][1]) % r;
		return res;
	}
};

matrix neutral(1, 0, 0, 1);
vector<matrix> tree(4 * 200001), tmp;

void build(int v, int l, int r) {
	if (r - l == 1) {
		tree[v] = tmp[l];
		return;
	}
	int m = (r + l) >> 1;
	build(2 * v + 1, l, m);
	build(2 * v + 2, m, r);
	tree[v] = tree[2 * v + 1] * tree[2 * v + 2];
}

matrix getMul(int v, int l, int r, int from, int to) {
	if (l >= to || r <= from) {
		return neutral;
	}
	if (l >= from && r <= to) {
		return tree[v];
	}
	else {
		int m = (l + r) >> 1;
		return getMul(2 * v + 1, l, m, from, to) * getMul(2 * v + 2, m, r, from ,to);
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("crypto.in", "r", stdin);
	freopen("crypto.out", "w", stdout);
	#endif
	scanf("%d%d%d", &r, &n, &m);
	for (int i = 0; i < n; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		tmp.push_back(matrix(a, b, c, d));
	}
	build(0, 0, n);
	for (int i = 0; i < m; i++) {
		int from, to;
		scanf("%d%d", &from, &to);
		matrix ans = getMul(0, 0, n, from - 1, to);
		printf("%d %d\n%d %d\n", ans.arr[0][0], ans.arr[0][1], ans.arr[1][0], ans.arr[1][1]);
	}
	return 0;
}