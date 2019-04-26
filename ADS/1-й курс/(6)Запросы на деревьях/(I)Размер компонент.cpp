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

const int MAXN = 1 << 17;
const int INF = 1e9;

struct node {
	int np, nc;
	bool w;
	node() {}
	node(int _np, int _nc, bool _w) {
		np = _np;
		nc = _nc;
		w = _w;
	}
};

vector<pair<int, int>> requests;
vector<int> parent, ranking, component_size;
map<pair<int, int>, vector<int>> link, cut;
vector<vector<pair<int, int>>> tree;
vector<node> commands;
int n, m;

int get_parent(int v) {
	if (parent[v] == v) {
		return v;
	}
	else {
		return get_parent(parent[v]);
	}
}

void add(int v, int vl, int vr, int l, int r, pair<int, int> e) {
	if (r < vl || vr < l) {
		return;
	}
	if (l <= vl && vr <= r) {
		tree[v].push_back(e);
		return;
	}
	int m = (vl + vr) / 2;
	add(v * 2, vl, m, l, r, e);
	add(v * 2 + 1, m + 1, vr, l, r, e);
}

bool solve(int v) {
	for (pair<int, int> now : tree[v]) {
		int pa = get_parent(now.first);
		int pb = get_parent(now.second);
		bool flag = false;
		if (ranking[pa] == ranking[pb]) {
			ranking[pa]++;
			flag = true;
		}
		if (ranking[pa] > ranking[pb]) {
			commands.push_back(node(pa, pb, flag));
			parent[pb] = pa;
			component_size[pa] += component_size[pb];
		}
		else {
			commands.push_back(node(pb, pa, flag));
			parent[pa] = pb;
			component_size[pb] += component_size[pa];
		}
	}
	if (v >= MAXN) {
		if (v - MAXN >= int(requests.size())) {
			return false;
		}
		cout <<  component_size[get_parent(requests[v - MAXN].second)] << endl;
	}
	else {
		if (!solve(2 * v)) {
			return false;
		}
		if (!solve(2 * v + 1)) {
			return false;
		}
	}
	for (int i = 0; i < tree[v].size(); i++) {
		node c = commands.back();
		commands.pop_back();
		parent[c.nc] = c.nc;
		component_size[c.np] -= component_size[c.nc];
		if (c.w) {
			ranking[c.np]--;
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("mail.in", "r", stdin);
	freopen("mail.out", "w", stdout);
	#endif*/
	cin >> n >> m;
	parent.resize(n + 1);
	ranking.resize(n + 1, 0);
	component_size.resize(n + 1, 1);
	tree.resize(2 * MAXN);
	for (int i = 0; i < m; i++) {
		string s;
		int u, v;
		cin >> s >> u;
		u--;
		if (s == "size") {
			requests.push_back(make_pair(i, u));
		}
		else if (s == "link") {
			cin >> v;
			v--;
			link[make_pair(min(u, v), max(u, v))].push_back(i);
		}
		else {
			cin >> v;
			v--;
			cut[make_pair(min(u, v), max(u, v))].push_back(i);
		}
	}
	if (requests.size() == 0) {
		return 0;
	}
	for (int i = 0; i < n; i++) {
		parent[i] = i;
	}
	for (auto now : link) {
		vector<int> l = now.second;
		vector<int> c = cut[now.first];
		if (c.size() < l.size()) {
			c.push_back(m);
		}
		int sz = l.size();
		for (int i = 0; i < sz; i++) {
			int left_pos = lower_bound(requests.begin(), requests.end(), make_pair(l[i], INF)) - requests.begin();
			int right_pos = lower_bound(requests.begin(), requests.end(), make_pair(c[i], -INF)) - requests.begin();
			right_pos--;
			if (left_pos > right_pos) {
				continue;
			}
			add(1, 0, MAXN - 1, left_pos, right_pos, now.first);
		}
	}
	solve(1);
	return 0;
}