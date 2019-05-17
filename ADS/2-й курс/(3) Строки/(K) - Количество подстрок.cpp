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
#include <bitset>
using namespace std;

typedef long long LL;

const LL INF = 1e18;
const int MAXLEN = 400000;

struct State {
	int length, link;
	LL dp = 0;
	map<char, int> next;
};

State states[MAXLEN * 2 + 1];
vector<bool> calculated(MAXLEN * 2 + 1, false);
int automataSize, last;

void initialize() {
	automataSize = last = 0;
	states[0].length = 0;
	states[0].link = -1;
	++automataSize;
}

void extend(char c) {
	int current = automataSize++, p;
	states[current].length = states[last].length + 1;
	for (p = last; p != -1 && !states[p].next.count(c); p = states[p].link) {
		states[p].next[c] = current;
	}
	if (p == -1)
		states[current].link = 0;
	else {
		int q = states[p].next[c];
		if (states[p].length + 1 == states[q].length)
			states[current].link = q;
		else {
			int clone = automataSize++;
			states[clone].length = states[p].length + 1;
			states[clone].next = states[q].next;
			states[clone].link = states[q].link;
			for (; p != -1 && states[p].next[c] == q; p = states[p].link)
				states[p].next[c] = clone;
			states[q].link = states[current].link = clone;
		}
	}
	last = current;
}

void calculateDP(int v) {
	if (calculated[v]) {
		return;
	}
	calculated[v] = true;
	states[v].dp += 1;
	for (auto i : states[v].next) {
		calculateDP(i.second);
		states[v].dp += states[i.second].dp;
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	#endif
	string t;
	cin >> t;
	initialize();
	for (int i = 0; i < t.length(); ++i) {
		extend(t[i]);
	}
	calculateDP(0);
	if (t.size() == 0) {
		cout << 0;
		return 0;
	}
	cout << states[0].dp - 1;
	return 0;
}