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
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef long long LL;

const LL INF = 1e9;

struct node {
	int index;
	int depth; //depth of vertex in tree
	vector<node*> up; //lca ancestors

	node() {}

	node(int ind, int l) {
		index = ind;
		up.resize(l + 1);
	}
};

vector<node*> tree;
vector<int> relation;
int l = 19;

int lca(int a, int b) {
	node *x = tree[a], *y = tree[b];
	if (x->depth < y->depth) {
		swap(x, y);
	}
	int ans = INF;
	int delta = x->depth - y->depth;
	int j = 0;
	while (x->depth != y->depth) {
		if (delta % 2 == 1) {
			x = x->up[j];
		}
		delta /= 2;
		j++;
	}
	if (x->index != y->index) {
		for (j = l; j >= 0; j--) {
			if (x->up[j] != y->up[j]) {
				x = x->up[j];
				y = y->up[j];
			}
		}
	}

	if (x->index != y->index) {
		x = x->up[0];
		y = y->up[0];
	}
	return x->index;
}

void add(int p, int num) {
	tree[num] = new node(num, l);
	tree[num]->depth = tree[p]->depth + 1;
	tree[num]->up[0] = tree[p];
	for (int i = 1; i <= l; i++) {
		tree[num]->up[i] = tree[num]->up[i - 1]->up[i - 1];
	}
}

int query(int a, int b) {
	int ancestor = lca(a, b);
	while (relation[ancestor] != ancestor) {
		ancestor = relation[ancestor];
	}
	return ancestor;
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	/*freopen("minonpath.in", "r", stdin);
	freopen("minonpath.out", "w", stdout);*/
	#endif
	int n, now_num = 2;
	scanf("%d\n", &n);
	tree.resize(n + 2);
	for (int i = 0; i <= n + 1; i++) {
		relation.push_back(i);
	}
	tree[1] = new node(1, l);
	tree[1]->up[0] = tree[1];
	for (int i = 1; i <= l; i++) {
		tree[1]->up[i] = tree[1]->up[i - 1]->up[i - 1];
	}
	tree[1]->depth = 0;
	for (int i = 0; i < n; i++) {
		char c;
		int a, b;
		scanf("%c", &c);
		if (c == '+') {
			scanf("%d\n", &a);
			add(a, now_num);
			now_num++;
		}
		else if (c == '-') {
			scanf("%d\n", &a);
			relation[a] = tree[a]->up[0]->index;
		}
		else {
			scanf("%d%d\n", &a, &b);
			printf("%d\n", query(a, b));
		}
	}
	return 0;
}