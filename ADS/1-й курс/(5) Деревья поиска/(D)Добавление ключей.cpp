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
	bool isZero = false;
	bool isLeftHasZero = false;
	bool isRightHasZero = false;
	tree(int _x) {
		value = _x;
		prior = rand();
		if (_x == 0)
			isZero = true;
	}
	void render() {
		id = 0;
		size = 1;
		if (l) {
			id += l->size;
			size += l->size;
			if (l->isLeftHasZero || l->isRightHasZero || l->isZero)
				isLeftHasZero = true;
			else
				isLeftHasZero = false;
		}
		else
			isLeftHasZero = false;
		if (r) {
			size += r->size;
			if (r->isLeftHasZero || r->isRightHasZero || r->isZero)
				isRightHasZero = true;
			else
				isRightHasZero = false;
		}
		else
			isRightHasZero = false;
	}
};

void split_key(tree *t, tree *&l, tree *&r, int key, int add = 0) {
	if (!t) {
		r = l = NULL;
		return;
	}
	int cur_key = add + t->id;
	if (key <= cur_key) {
		split_key(t->l, l, t->l, key, add);
		r = t;
		if (r)
			r->render();
	}
	else {
		split_key(t->r, t->r, r, key, add + 1 + t->id);
		l = t;
		if (l)
			l->render();
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
		if (r)
			r->render();
	}
	else {
		split(t->r, t->r, r, value);
		l = t;
		if (l)
			l->render();
	}
	if (t)
		t->render();
}

void merge(tree *&t, tree *l, tree *r) {
	if (l)
		l->render();
	if (r)
		r->render();
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

void findZero(tree *t, int &ind) {
	if (!t->isLeftHasZero && t->isZero) {
		ind += t->id + 1;
		return;
	}
	if (t->isLeftHasZero) {
		findZero(t->l, ind);
	}
	else if (t->isRightHasZero) {
		ind += t->id + 1;
		findZero(t->r, ind);
	}
}

vector<int> ans;

void fillAns(tree *t) {
	if (!t)
		return;
	fillAns(t->l);
	//cout << t->value << ' ';
	ans.push_back(t->value);
	fillAns(t->r);
}

void print(tree *t) {
	if (!t)
		return;
	print(t->l);
	cout << t->value << ' ';
	print(t->r);
}

int main() {
	/*freopen("input.txt", "r", stdin);
	freopen("ideal.txt", "w", stdout);
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	#endif*/
	int n, m;
	cin >> n >> m;
	tree *t = NULL;
	for (int i = 0; i <= n + m; i++) {
		add(t, 0);
	}
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		tree *l, *mid, *r;
		split_key(t, l, r, x);
		split_key(l, l, mid, x - 1);
		if (mid->value == 0) {
			mid->value = i + 1;
			mid->isZero = false;
		}
		else {
			merge(mid, new tree(i + 1), mid);
			int ind = 0;
			findZero(r, ind);
			tree *ll, *rr, *mm;
			split_key(r, ll, rr, ind);
			split_key(ll, ll, mm, ind - 1);
			merge(r, ll, rr);
		}
		merge(r, mid, r);
		merge(t, l, r);
	}
	fillAns(t);
	while (ans.size() > 0 && ans.back() == 0)
		ans.pop_back();
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << ' ';
	return 0;
}