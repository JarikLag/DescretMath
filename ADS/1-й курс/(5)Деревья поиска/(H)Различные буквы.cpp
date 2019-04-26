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
	tree *l = NULL, *r = NULL;
	int id = 0;
	int size = 1;
	double prior;
	char letter;
	int letterNum;
	int listOfLetters;
	tree(char c, int num) {
		letter = c;
		letterNum = num;
		listOfLetters = (1 << (letter - 'a'));
		size = num;
		id = num - 1;
		prior = rand();
	}
	void render() {
		id = 0;
		size = 1;
		listOfLetters = (1 << (letter - 'a'));
		if (l) {
			id += l->size;
			size += l->size;
			listOfLetters |= l->listOfLetters;
		}
		if (r) {
			size += r->size;
			listOfLetters |= r->listOfLetters;
		}
	}
};

void create(tree *&t) {
	tree *tempL= NULL, *tempR = NULL;
	if (t->letterNum == 2) {
		t->letterNum = 1;
		tempL = new tree(t->letter, 1);
		if (t->l) {
			tempL->prior = (t->prior + t->l->prior) / 2;
			tempL->l = t->l;
		}
		else {
			tempL->prior = t->prior - rand() - 1;
		}
		t->l = tempL;
		t->render();
		return;
	} else if (t->letterNum % 2 == 0) {
		t->letterNum--;
		tempL = new tree(t->letter, t->letterNum / 2);
		tempR = new tree(t->letter, t->letterNum - (t->letterNum / 2));
		t->letterNum = 1;
	}
	else {
		tempL = new tree(t->letter, t->letterNum / 2);
		tempR = new tree(t->letter, t->letterNum / 2);
		t->letterNum = 1;
	}
	if (t->l) {
		tempL->prior = (t->prior + t->l->prior) / 2;
		tempL->l = t->l;
	}
	else {
		tempL->prior = t->prior - rand() - 1;
	}
	t->l = tempL;
	if (t->r) {
		tempR->prior = (t->prior + t->r->prior) / 2;
		tempR->r = t->r;
	}
	else {
		tempR->prior = t->prior - rand() - 1;
	}
	t->r = tempR;
	t->render();
}

void split_key(tree *t, tree *&l, tree *&r, int key, int add = 0) {
	if (!t) {
		r = l = NULL;
		return;
	}
	if (t->letterNum > 1) {
		create(t);
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

void merge(tree *&t, tree *l, tree *r) {
	if (l && l->letterNum > 1) {
		create(l);
	}
	if (r && r->letterNum > 1) {
		create(r);
	}
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

void add(tree *&t, int key, int sz, char c) {
	tree *t1, *t2;
	split_key(t, t1, t2, key);
	merge(t1, t1, new tree(c, sz));
	merge(t, t1, t2);
}

void del(tree *&t, int ql, int qr) {
	tree *l1, *r1, *l2, *r2;
	split_key(t, l1, r1, qr);
	split_key(l1, l2, r2, ql - 1);
	merge(t, l2, r1);
}

int query(tree *t, int ql, int qr) {
	tree *l1, *r1, *l2, *r2;
	split_key(t, l1, r1, qr);
	split_key(l1, l2, r2, ql - 1);
	int ans = r2->listOfLetters;
	merge(l1, l2, r2);
	merge(t, l1, r1);
	return ans;
}

void print(tree *t) {
	if (!t)
		return;
	print(t->l);
	for (int i = 0; i < t->letterNum; i++) {
		cout << t->letter;
	}
	print(t->r);
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("log.in", "r", stdin);
	freopen("log.out", "w", stdout);
	#endif
	int n;
	tree *t = NULL;
	cin >> n;
	for (int i = 0; i < n; i++) {
		char c, letter;
		int a, b;
		cin >> c >> a >> b;
		if (c == '+') {
			cin >> letter;
			if (!t)
				t = new tree(letter, b);
			else {
				add(t, a - 1, b, letter);
			}
		}
		else if (c == '-') {
			del(t, a, a + b - 1);
		}
		else {
			int ans = query(t, a, b);
			int count = 0;
			while (ans != 0) {
				count++;
				ans = ans & (ans - 1);
			}
			cout << count << endl;
		}
		/*print(t);
		cout << endl;*/
	}
	return 0;
}