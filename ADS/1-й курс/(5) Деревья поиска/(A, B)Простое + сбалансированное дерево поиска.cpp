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

struct tree {
	int x, y;
	tree *l, *r;
	tree(int x) : x(x), y(rand()), l(NULL), r(NULL) {};
};

void split(tree *t, int x, tree *&l, tree *&r) {
	if (t == NULL) {
		l = r = NULL;
		return;
	}
	if (t->x <= x) {
		tree *l2, *r2;
		split(t->r, x, l2, r2);
		t->r = l2;
		r = r2;
		l = t;
	}
	else {
		split(t->l, x, l, t->l);
		r = t;
	}
}

tree *merge_tree(tree *l, tree *r) {
	if (l == NULL) {
		return r;
	}
	if (r == NULL) {
		return l;
	}
	if (l->y >= r->y) {
		l->r = merge_tree(l->r, r);
		return l;
	}
	else {
		r->l = merge_tree(l, r->l);
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

tree* next(int x, tree *t) {
	tree *current = t, *successor = NULL;
	while (current != NULL) {
		if (current->x > x) {
			successor = current;
			current = current->l;
		}
		else {
			current = current->r;
		}
	}
	return successor;
}

tree* prev(int x, tree *t) {
	tree *current = t, *successor = NULL;
	while (current != NULL) {
		if (current->x < x) {
			successor = current;
			current = current->r;
		}
		else {
			current = current->l;
		}
	}
	return successor;
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
	string s;
	int x;
	while (cin >> s) {
		cin >> x;
		bool flag = false;
		if (s == "insert") {
			if (t == NULL)
				t = new tree(x);
			else 
				add(t, x);
		}			
		else if (s == "delete")
			del(t, x);
		else if (s == "exists") {
			find_tree(t, x, flag);
			if (flag)
				cout << "true" << endl;
			else
				cout << "false" << endl;
		}
		else if (s == "next") {
			tree *now = next(x, t);
			if (now == NULL || now->x <= x) {
				cout << "none" << endl;
			}
			else {
				cout << now->x << endl;
			}
		}
		else if (s == "prev") {
			tree *now = prev(x, t);
			if (now == NULL || now->x >= x) {
				cout << "none" << endl;
			}
			else {
				cout << now->x << endl;
			}
		}
	}
	return 0;
}