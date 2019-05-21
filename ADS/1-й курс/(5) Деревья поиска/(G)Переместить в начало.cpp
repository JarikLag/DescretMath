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
	tree *l = NULL, *r = NULL;
	int id = 0;
	int size = 1;
	int value, prior;
	tree(int _x) {
		value = _x;
		prior = rand();
	}
	void render() {
		id = 0;
		size = 1;
		if (l) {
			id += l->size;
			size += l->size;
		}
		if (r)
			size += r->size;
	}
};

int cnt(tree *t) {
	return t ? t->size : 0;
}

void update_cnt(tree *t) {
	if (t)
		t->size = 1 + cnt(t->l) + cnt(t->r);
}

void split_key(tree *t, tree *&l, tree *&r, int key, int add = 0) {
	if (!t) {
		r = l = NULL;
		return;
	}
	int cur_key = add + t->id;
	if (key <= cur_key) {
		split_key(t->l, l, t->l, key, add);
		r = t;
	}
	else {
		split_key(t->r, t->r, r, key, add + 1 + t->id);
		l = t;
	}
	if (t)
		t->render();
}

void split(tree *t, tree *&l, tree *&r, int value) {
	if (!t) {
		r = l = NULL;
		return;
	}
	if (value <= t->value) {
		split(t->l, l, t->l, value);
		r = t;
	}
	else {
		split(t->r, t->r, r, value);
		l = t;
	}
	if (t)
		t->render();
}

void merge(tree *&t, tree *l, tree *r) {
	if (!l || !r) {
		t = l ? l : r;
	}
	else {
		if (l->prior > r->prior) {
			merge(l->r, l->r, r);
			t = l;
		}
		else {
			merge(r->l, l, r->l);
			t = r;
		}
	}
	if (t)
		t->render();
}

void add(tree *&t, int value) {
	tree *t1, *t2;
	split(t, t1, t2, value);
	merge(t1, t1, new tree(value));
	merge(t, t1, t2);
}

void find_max(tree *t, int key, int add = 0) {
	if (!t)
		return;
	int cur_key = add + t->id;
	if (cur_key == key) {
		cout << t->value << endl;
		return;
	}
	if (key < cur_key) {
		find_max(t->l, key, add);
	}
	else {
		find_max(t->r, key, add + 1 + t->id);
	}
}

void erase(tree *&t, int x, int add = 0) {
	if (!t)
		return;
	if (t->value == x) {
		merge(t, t->l, t->r);
		return;
	}
	if (x <= t->value) {
		erase(t->l, x, add);
	}
	else {
		erase(t->r, x, 1 + add + t->id);
	}
	t->render();
}

void print(tree *t) {
	if (!t)
		return;
	print(t->l);
	cout << t->value << ' ';
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
	int n, m;
	cin >> n >> m;
	tree *t = NULL;
	for (int i = 1; i <= n; i++) {
		add(t, i);
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		tree *l, *mid, *r;
		split_key(t, l, r, b);
		split_key(l, l, mid, a - 1);
		merge(r, l, r);
		merge(t, mid, r);
	}
	print(t);
	return 0;
}