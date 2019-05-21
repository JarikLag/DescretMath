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

const int INF = 1e9 + 100;

struct tree {
	LL sum = 0, maxHeight = 0;
	LL delta = -INF;
	int left, right;
	tree *rightChild = NULL, *leftChild = NULL;
	tree(int l, int r) {
		left = l;
		right = r;
	}
};

void push(tree *t) {
	int m = (t->left + t->right) >> 1;
	if (t->leftChild == NULL || t->rightChild == NULL) {
		t->leftChild = new tree(t->left, m);
		t->rightChild = new tree(m, t->right);
	}		
	if (t->delta == -INF)
		return;	
	t->leftChild->delta = t->rightChild->delta = t->delta;
	t->leftChild->sum = t->leftChild->maxHeight = t->delta * (m - t->left);
	t->rightChild->sum = t->rightChild->maxHeight = t->delta * (t->right - m);
	t->delta = -INF;
}

void modify(tree *t, int from, int to, int val) {
	if (t->left >= to || t->right <= from)
		return;
	if (t->left >= from && t->right <= to) {
		t->delta = val;
		t->sum = t->maxHeight = val * (t->right - t->left);
		return;
	}
	push(t);
	int m = (t->left + t->right) >> 1;
	modify(t->leftChild, from, to, val);
	modify(t->rightChild, from, to, val);
	t->sum = t->leftChild->sum + t->rightChild->sum;
	t->maxHeight = max(t->leftChild->maxHeight, t->rightChild->maxHeight + t->leftChild->sum);
}

int getIndex(tree *t, LL val) {
	if (t->right - t->left == 1) {
		if (t->sum > val)
			return t->left;
		else
			return t->right;
	}
	push(t);
	if (t->leftChild->maxHeight > val)
		return getIndex(t->leftChild, val);
	else
		return getIndex(t->rightChild, val - t->leftChild->sum);
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	#endif*/
	int n;
	cin >> n;
	tree *t = new tree(0, n);
	char c = '0';
	while (c != 'E') {
		cin >> c;
		if (c == 'Q') {
			int h;
			cin >> h;
			cout << getIndex(t, h) << endl;
		}
		else {
			int a, b;
			LL d;
			cin >> a >> b >> d;
			modify(t, a - 1, b, d);
		}
	}
	return 0;
}