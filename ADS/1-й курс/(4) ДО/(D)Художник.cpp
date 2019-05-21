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
using namespace std;

typedef long long LL;

//0 - white, 1 - black
//first - number, second - length
const int base = 500010;
vector<pair<int, int> > tree(8 * base, make_pair(0, 0));
vector<int> setColor(8 * base, -1);
vector<bool> isBlackPrefix(8 * base, false), isBlackSuffix(8 * base, false), isBlackFull(8 * base, false);

void push(int v, int l, int r) {
	if (setColor[v] == -1)
		return;
	if (r - l == 1) {
		tree[v].first = tree[v].second = setColor[v];
		isBlackFull[v] = isBlackPrefix[v] = isBlackSuffix[v] = bool(setColor[v]);
		setColor[v] = -1;
		return;
	}
	setColor[2 * v + 1] = setColor[2 * v + 2] = setColor[v];
	tree[2 * v + 1].first = tree[2 * v + 2].first = setColor[v];
	if (setColor[v] == 0) {
		tree[2 * v + 1].second = tree[2 * v + 2].second = 0;
		isBlackFull[2 * v + 1] = isBlackPrefix[2 * v + 1] = isBlackSuffix[2 * v + 1] = false;
		isBlackFull[2 * v + 2] = isBlackPrefix[2 * v + 2] = isBlackSuffix[2 * v + 2] = false;	
	}
	else {
		int m = (l + r) / 2;
		tree[2 * v + 1].second = m - l;
		tree[2 * v + 2].second = r - m;
		isBlackFull[2 * v + 1] = isBlackPrefix[2 * v + 1] = isBlackSuffix[2 * v + 1] = true;
		isBlackFull[2 * v + 2] = isBlackPrefix[2 * v + 2] = isBlackSuffix[2 * v + 2] = true;
	}
	setColor[v] = -1;
}

void modify(int v, int l, int r, int from, int to, int color) {
	push(v, l, r);
	if (l >= to || r <= from)
		return;
	if (l >= from && r <= to) {
		if (color == 1) {
			tree[v].first = 1;
			tree[v].second = r - l;
			setColor[v] = 1;
			isBlackFull[v] = isBlackPrefix[v] = isBlackSuffix[v] = true;
			return;
		}
		else {
			tree[v].first = 0;
			tree[v].second = 0;
			setColor[v] = 0;
			isBlackFull[v] = isBlackPrefix[v] = isBlackSuffix[v] = false;
			return;
		}
	}
	else {
		int m = (l + r) / 2;
		modify(2 * v + 1, l, m, from, to, color);
		modify(2 * v + 2, m, r, from, to, color);
		push(v, l, r);
		tree[v].second = tree[2 * v + 1].second + tree[2 * v + 2].second;
		if (isBlackFull[2 * v + 1] && isBlackFull[2 * v + 2]) {
			tree[v].first = 1;
			isBlackFull[v] = isBlackPrefix[v] = isBlackSuffix[v] = true;
		}
		else if (isBlackFull[2 * v + 1] && isBlackPrefix[2 * v + 2]) {
			tree[v].first = tree[2 * v + 1].first + tree[2 * v + 2].first - 1;
			isBlackFull[v] = false;
			isBlackPrefix[v] = true;
			isBlackSuffix[v] = isBlackSuffix[2 * v + 2];
		}
		else if (isBlackSuffix[2 * v + 1] && isBlackFull[2 * v + 2]) {
			tree[v].first = tree[2 * v + 1].first + tree[2 * v + 2].first - 1;
			isBlackFull[v] = false;
			isBlackPrefix[v] = isBlackPrefix[2 * v + 1];
			isBlackSuffix[v] = true;			
		} else if (isBlackSuffix[2 * v + 1] && isBlackPrefix[2 * v + 2]) {
			tree[v].first = tree[2 * v + 1].first + tree[2 * v + 2].first - 1;
			isBlackFull[v] = false;
			isBlackPrefix[v] = isBlackPrefix[2 * v + 1];
			isBlackSuffix[v] = isBlackSuffix[2 * v + 2];
		}
		else {
			tree[v].first = tree[2 * v + 1].first + tree[2 * v + 2].first;
			isBlackFull[v] = false;
			isBlackPrefix[v] = isBlackPrefix[2 * v + 1];
			isBlackSuffix[v] = isBlackSuffix[2 * v + 2];
		}
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("painter.in", "r", stdin);
	freopen("painter.out", "w", stdout);
	#endif
	
	int n;
	cin >> n;
	char c;
	int l, r, cl;
	for (int i = 0; i < n; i++) {
		cin >> c >> l >> r;
		l += base;
		r += l;
		if (c == 'W')
			cl = 0;
		else
			cl = 1;
		modify(0, 0, base * 2, l, r, cl);
		cout << tree[0].first << ' ' << tree[0].second << endl;
	}
	return 0;
}