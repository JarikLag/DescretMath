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

const LL INF = 1e18;

struct node {
	LL index; //in arr
	LL size; //size of subtree
	LL path_size; //size of path
	LL seg_index; //index of segtree
	LL depth; //depth of vertex in tree
	bool is_heavy; //is edge to parent heavy
	vector<node*> up; //lca ancestors
	vector<node*> children;

	node(LL ind, LL l) {
		index = ind;
		size = 1;
		path_size = 1;
		is_heavy = false;
		up.resize(l + 1);
	}
};

struct segtree {
	LL root; //index of root
	LL logic_size; //lenght of path
	vector<LL> tree;
	vector<LL> add;

	segtree() {}

	segtree(LL rt, LL sz) {
		root = rt;
		logic_size = sz;
		tree.resize(4 * sz);
		add.resize(4 * sz, 0);
	}

	void push(LL v, LL l, LL r) {
		if (r - l == 1) {
			add[v] = 0;
			return;
		}
		if (add[v] != 0) {
			add[2 * v + 1] += add[v];
			add[2 * v + 2] += add[v];
			tree[2 * v + 1] += add[v];
			tree[2 * v + 2] += add[v];
			add[v] = 0;
		}
		tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
	}

	LL get_sum(LL v, LL l, LL r, LL from, LL to) {
		push(v, l, r);
		if (l >= to || r <= from)
			return 0;
		if (l >= from && r <= to) {
			return tree[v];
		}
		else {
			LL m = (l + r) / 2;
			return get_sum(2 * v + 1, l, m, from, to) + get_sum(2 * v + 2, m, r, from, to);
		}
	}

	void add_all(LL v, LL l, LL r, LL from, LL to, LL val) {
		push(v, l, r);
		if (l >= to || r <= from)
			return;
		if (l >= from && r <= to) {
			tree[v] += val;
			add[v] = val;
		}
		else {
			push(v, l, r);
			LL m = (l + r) / 2;
			add_all(2 * v + 1, l, m, from, to, val);
			add_all(2 * v + 2, m, r, from, to, val);
			push(v, l, r);
		}
	}
};

vector<node*> node_arr;
vector<segtree*> segtree_arr;
vector<LL> time_in, time_out;
LL timer = 0, l;

void dfs(node *v, LL p = 0, LL depth = 0) {
	time_in[v->index] = ++timer;
	v->up[0] = node_arr[p];
	for (LL i = 1; i <= l; i++) {
		v->up[i] = v->up[i - 1]->up[i - 1];
	}
	for (node* to : v->children) {
		if (to->index != p) {
			dfs(to, v->index, depth + 1);
			v->size += to->size;
		}
	}
	for (node *to : v->children) {
		if (to != v->up[0] && 2 * to->size >= v->size) {
			to->is_heavy = true;
			break;
		}
	}
	time_out[v->index] = ++timer;
	v->depth = depth;
}

bool is_upper(node *u, node *v) {
	return time_in[u->index] <= time_in[v->index] && time_out[u->index] >= time_out[v->index];
}

node* lca(node *u, node *v) {
	if (is_upper(u, v)) {
		return u;
	}
	if (is_upper(v, u)) {
		return v;
	}
	for (LL i = l; i >= 0; i--) {
		if (!is_upper(u->up[i], v)) {
			u = u->up[i];
		}
	}
	return u->up[0];
}

void segtree_dfs(node *v, LL now_segtree) {
	if (!v->is_heavy) {
		now_segtree = segtree_arr.size();
		segtree_arr.push_back(new segtree());
	}
	for (node *to : v->children) {
		if (to != v->up[0]) {
			segtree_dfs(to, now_segtree);
			if (to->is_heavy) {
				v->path_size += to->path_size;
			}
		}
	}
	if (!v->is_heavy) {
		segtree_arr[now_segtree] = new segtree(v->index, v->path_size);
	}
	v->seg_index = now_segtree;
}

void modify(node *u, node *v, LL s) {
	node *ancestor = lca(u, v);
	do {
		node *now_root = node_arr[segtree_arr[u->seg_index]->root];
		LL to = u->depth - now_root->depth + 1;
		LL length = now_root->path_size;
		if (u->seg_index == ancestor->seg_index) {
			LL from = ancestor->depth - now_root->depth;
			segtree_arr[u->seg_index]->add_all(0, 0, length, from, to, s);
			break;
		}
		segtree_arr[u->seg_index]->add_all(0, 0, length, 0, to, s);
		u = now_root->up[0];
		if (u == ancestor) {
			now_root = node_arr[segtree_arr[u->seg_index]->root];
			LL from = u->depth - now_root->depth;
			LL length = now_root->path_size;
			segtree_arr[u->seg_index]->add_all(0, 0, length, from, from + 1, s);
		}
	} while (u != ancestor);
	do {
		node *now_root = node_arr[segtree_arr[v->seg_index]->root];
		LL to = v->depth - now_root->depth + 1;
		LL length = now_root->path_size;
		if (v->seg_index == ancestor->seg_index) {
			LL from = ancestor->depth - now_root->depth;
			segtree_arr[v->seg_index]->add_all(0, 0, length, from, to, s);
			break;
		}
		segtree_arr[v->seg_index]->add_all(0, 0, length, 0, to, s);
		v = now_root->up[0];
		if (v == ancestor) {
			now_root = node_arr[segtree_arr[v->seg_index]->root];
			LL from = v->depth - now_root->depth;
			LL length = now_root->path_size;
			segtree_arr[v->seg_index]->add_all(0, 0, length, from, from + 1, s);
		}
	} while (v != ancestor);
	node *now_root = node_arr[segtree_arr[ancestor->seg_index]->root];
	LL length = now_root->path_size;
	LL from = ancestor->depth - now_root->depth;
	segtree_arr[ancestor->seg_index]->add_all(0, 0, length, from, from + 1, -s);
}

LL query(node *v) {
	node *now_root = node_arr[segtree_arr[v->seg_index]->root];
	LL length = now_root->path_size;
	LL from = v->depth - now_root->depth;
	return segtree_arr[v->seg_index]->get_sum(0, 0, length, from, from + 1);
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	/*freopen("minonpath.in", "r", stdin);
	freopen("minonpath.out", "w", stdout);*/
	#endif
	LL n, m;
	scanf("%lld\n", &n);
	l = log2(n);
	time_in.resize(n + 1, 0);
	time_out.resize(n + 1, 0);
	for (LL i = 0; i < n; i++) {
		node_arr.push_back(new node(i, l));
	}
	for (LL i = 0; i < n - 1; i++) {
		LL u, v;
		scanf("%lld%lld\n", &u, &v);
		u--, v--;
		node_arr[u]->children.push_back(node_arr[v]);
		node_arr[v]->children.push_back(node_arr[u]);
	}
	dfs(node_arr[0]);
	segtree_dfs(node_arr[0], 0);
	scanf("%lld\n", &m);
	for (LL i = 0; i < m; i++) {
		LL u, v, s;
		char c;
		scanf("%c ", &c);
		if (c == '+') {
			scanf("%lld%lld%lld\n", &u, &v, &s);
			modify(node_arr[u - 1], node_arr[v - 1], LL(s));
		}
		else {
			scanf("%lld\n", &u);
			LL ans = query(node_arr[u - 1]);
			printf("%lld\n", ans);
		}
	}
	return 0;
}