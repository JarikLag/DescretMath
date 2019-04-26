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
	tree *l = NULL, *r = NULL, *p = NULL;
	int id = 0;
	int size = 1;
	int value, prior;
	bool reverse = false;
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

map<tree*, int> type; //0 - line, 1 - cycle
vector<tree*> vertex;

void push(tree *t) {
	if (t && t->reverse) {
		t->reverse = false;
		swap(t->l, t->r);
		if (t->l)
			t->l->reverse ^= true;
		if (t->r)  
			t->r->reverse ^= true;
		t->render();
	}
}

void fillParent(tree *&t) {
	if (t && t->l)
		t->l->p = t;
	if (t && t->r)
		t->r->p = t;
}

void split_key(tree *t, tree *&l, tree *&r, int key, int add = 0) {
	if (!t) {
		r = l = NULL;
		return;
	}
	push(t);
	int cur_key = add + t->id;
	if (key <= cur_key) {
		split_key(t->l, l, t->l, key, add);
		fillParent(t);
		r = t;
	}
	else {
		split_key(t->r, t->r, r, key, add + 1 + t->id);
		fillParent(t);
		l = t;
	}
	if (t)
		t->render();
}

void merge(tree *&t, tree *l, tree *r) {
	push(l);
	push(r);
	if (!l || !r) {
		t = l ? l : r;
	}
	else {
		if (l->prior > r->prior) {
			merge(l->r, l->r, r);
			fillParent(l);
			t = l;
		}
		else {
			merge(r->l, l, r->l);
			fillParent(r);
			t = r;
		}
	}
	if (t)
		t->render();
}

void reverse(tree *&t) {
	t->reverse ^= true;
}

void pushAll(tree *v) {
	vector<int> direction; //0 - left, 1 - right
	tree *tmp = v;
	while (tmp->p) {
		if (tmp->p->r == tmp)
			direction.push_back(1);
		else
			direction.push_back(0);
		tmp = tmp->p;
	}
	bool rev = false;
	while(tmp != v) {
		if (tmp && tmp->reverse) {
			tmp->reverse = false;
			swap(tmp->l, tmp->r);
			if (tmp->l)
				tmp->l->reverse ^= true;
			if (tmp->r)
				tmp->r->reverse ^= true;
			tmp->render();
			rev = true;
		}
		else {
			rev = false;
		}
		if (rev) {
			if (direction.back())
				tmp = tmp->l;
			else
				tmp = tmp->r;
		}
		else {
			if (!direction.back())
				tmp = tmp->l;
			else
				tmp = tmp->r;
		}
		direction.pop_back();
	}
	push(v);
}

int getIndex(tree *v) {
	pushAll(v);
	int ans = v->id;
	tree *tmp = v;
	while (tmp->p) {
		if (tmp->p->r == tmp)
			ans += tmp->p->id + 1;
		tmp = tmp->p;	
	}
	return ans;
}

tree* getParent(tree *v) {
	tree *tmp = v;
	while (tmp->p) {
		tmp = tmp->p;
	}
	return tmp;
}

void connect(int a, int b) {
	tree *l = getParent(vertex[a]), *r = getParent(vertex[b]);
	if (l == r)
		type[l] = 1;
	else {
		if (getIndex(vertex[a]) == 0 && getIndex(vertex[b]) == 0) {
			reverse(l);
		}
		else if (getIndex(vertex[a]) == 0 && getIndex(vertex[b]) == r->size - 1) {
			reverse(r);
			reverse(l);
		} 
		else if (getIndex(vertex[a]) == l->size - 1 && getIndex(vertex[b]) == r->size - 1) {
			reverse(r);
		}
		tree *now = NULL;
		merge(now, l, r);
		type.erase(l);
		type.erase(r);
		type[now] = 0;
	}
}

void disconnect(int a, int b) {
	tree *t = getParent(vertex[a]);
	if (type[t] == 1) {
		type.erase(t);
		int indA = getIndex(vertex[a]), indB = getIndex(vertex[b]);
		if (abs(indA - indB) != t->size - 1) {
			tree *l, *r;
			split_key(t, l, r, min(indA, indB) + 1);
			if (l)
				l->p = NULL;
			if (r)
				r->p = NULL;
			merge(t, r, l);
		}
		type[t] = 0;
	}
	else {
		type.erase(t);
		int indA = getIndex(vertex[a]), indB = getIndex(vertex[b]);
		tree *l, *r;
		split_key(t, l, r, min(indA, indB) + 1);
		if (l)
			l->p = NULL;
		if (r)
			r->p = NULL;
		type[l] = type[r] = 0;
	}
}

int query(int a, int b) {
	tree *l = getParent(vertex[a]), *r = getParent(vertex[b]);
	if (l == r) {
		int fi = getIndex(vertex[a]), si = getIndex(vertex[b]);
		if (type[l] == 0) {			
			return abs(fi - si) - 1;
		}
		else {
			int tmp = min(l->size - 1 - fi, l->size - 1 - si) + min(fi, si);
			return min(abs(fi - si) - 1, tmp);
		}
	}
	else
		return -1;
}

void print(tree *t) {
	if (!t)
		return;
	push(t);
	print(t->l);
	cout << t->value << ' ';
	print(t->r);
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("roads.in", "r", stdin);
	freopen("roads.out", "w", stdout);
	#endif
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	vertex.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		tree *now = new tree(i);
		type[now] = 0;
		vertex[i] = now;
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		connect(a, b);
	}
	for (int i = 0; i < q; i++) {
		char c;
		int a, b;
		scanf("\n%c%d%d", &c, &a, &b);
		if (c == '?') {
			if (a == b)
				printf("%d\n", 0);
			else
				printf("%d\n", query(a, b));
		}
		else if (c == '+') {
			connect(a, b);
		}
		else {
			disconnect(a, b);
		}
	}
	return 0;
}