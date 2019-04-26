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

const LL INF = 1e18;

struct tree {
	LL sum = 0;
	int x, y;
	tree *l, *r;
	tree(int x) : x(x), y(rand()), sum(x), l(NULL), r(NULL) {};
};

void update(tree *t) {
	if (t == NULL)
		return;
	t->sum = t->x;
	if (t->l) {
		t->sum += t->l->sum;
	}
	if (t->r) {
		t->sum += t->r->sum;
	}
}

void split(tree *t, int x, tree *&l, tree *&r) {
	if (t == NULL) {
		l = r = NULL;
		return;
	}
	if (t->x <= x) {
		split(t->r, x, t->r, r);
		l = t;
	}
	else {
		split(t->l, x, l, t->l);
		r = t;
	}
	update(t);
}

tree *merge_tree(tree *l, tree *r) {
	if (l == NULL)
		return r;
	if (r == NULL)
		return l;
	if (l->y >= r->y) {
		l->r = merge_tree(l->r, r);
		update(l);
		return l;
	}
	else {
		r->l = merge_tree(l, r->l);
		update(r);
		return r;
	}
}

void add(tree *&t, int x) {
	tree *l, *r;
	split(t, x, l, r);
	t = merge_tree(merge_tree(l, new tree(x)), r);
}

void del(tree *&t, int x) {
	tree *l, *r;
	split(t, x, l, r);
	tree *l2, *r2;
	split(l, x - 1, l2, r2);
	t = merge_tree(l2, r);
}

void find_tree(tree *t, int x, bool &flag) {
	if (t == NULL)
		return;
	if (t->x == x) {
		flag = true;
		return;
	}
	else {
		if (t->x > x) {
			find_tree(t->l, x, flag);
		}
		else {
			find_tree(t->r, x, flag);
		}
	}
	return;
}

LL sum_tree(tree *t, int ql, int qr) {
	tree *l2, *l3, *r2, *r3;
	split(t, ql - 1, l2, r2);
	split(r2, qr, l3, r3);
	if (l3 == NULL) {
		t = merge_tree(l2, merge_tree(l3, r3));
		return 0;
	}
	LL ans = l3->sum;
	t = merge_tree(l2, merge_tree(l3, r3));
	return ans;
}

void print(tree *t) {
	if (!t) {
		cout << "end" << endl;
		return;
	}
	cout << "x : " << t->x << " sum : " << t->sum << endl;
	print(t->l);
	print(t->r);
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	#endif*/
	tree *t = NULL;
	int n, mod = 1e9;
	LL pr = 0;
	char prev = '-';
	cin >> n;
	for (int i = 0; i < n; i++) {
		char c; int a, b;
		cin >> c >> a;
		if (c == '?')
			cin >> b;
		if (c == '+') {
			bool flag = false;
			if (prev != '?') {
				find_tree(t, a, flag);
				if (flag == false)
					add(t, a);
			}
			else {
				int keuk = (a + pr) % mod;
				find_tree(t, keuk, flag);
				if (flag == false)
					add(t, keuk);
			}
		}
		else {
			pr = sum_tree(t, a, b);
			cout << pr << endl;
		}
		prev = c;
	}
	return 0;
}