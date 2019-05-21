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
	int x, y, num;
	tree  *l, *r, *p;
	tree(int x, int y, int num) : x(x), y(y), num(num), l(NULL), r(NULL), p(NULL) {};
};

tree *merge_tree(tree *l, tree *r) {
	if (l == NULL) {
		return r;
	}
	if (r == NULL) {
		return l;
	}
	if (l->y <= r->y) {
		l->r = merge_tree(l->r, r);
		l->r->p = l;
		return l;
	}
	else {
		r->l = merge_tree(l, r->l);
		r->l->p = r;
		return r;
	}
}

bool comp(tree *a, tree *b) {
	return (a->x > b->x);
}

vector<pair<pair<int, int>, int>> ans;

void fillAns(tree *t) {
	pair<pair<int, int>, int> now;
	if (t->p)
		now.first.first = t->p->num;
	else
		now.first.first = 0;
	if (t->l)
		now.first.second = t->l->num;
	else
		now.first.second = 0;
	if (t->r)
		now.second = t->r->num;
	else
		now.second = 0;
	ans[t->num] = now;
	if (t->l)
		fillAns(t->l);
	if (t->r)
		fillAns(t->r);
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
	scanf("%d", &n);
	vector<tree*> v;
	for (int i = 0; i < n; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		v.push_back(new tree(a, b, i + 1));
	}
	sort(v.begin(), v.end(), comp);
	queue<tree*> q1, q2;
	for (int i = 0; i < n; i++) {
		q1.push(v[i]);
	}
	int turn = 1;
	while (1) {
		if (turn == 1) {
			while (q1.size() > 1) {
				tree *first = q1.front();
				q1.pop();
				tree *second = q1.front();
				q1.pop();
				tree *t;
				t = merge_tree(second, first);
				q2.push(t);
			}
			if (q1.size() == 1) {
				q2.push(q1.front());
				q1.pop();
			}
			turn = 2;
			if (q2.size() == 1)
				break;			
		}
		else {
			while (q2.size() > 1) {
				tree *first = q2.front();
				q2.pop();
				tree *second = q2.front();
				q2.pop();
				tree *t;
				t = merge_tree(second, first);
				q1.push(t);
			}
			if (q2.size() == 1) {
				q1.push(q2.front());
				q2.pop();	
			}
			turn = 1;
			if (q1.size() == 1)
				break;
		}
	}
	ans.resize(n + 1);
	if (turn == 1)
		fillAns(q1.front());
	else
		fillAns(q2.front());
	cout << "YES" << endl;
	for (int i = 1; i <= n; i++) {
		printf("%d %d %d\n", ans[i].first.first, ans[i].first.second, ans[i].second);
	}
	return 0;
}