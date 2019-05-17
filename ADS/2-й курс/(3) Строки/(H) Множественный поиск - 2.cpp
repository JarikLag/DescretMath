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
const int MAXLEN = 1000000;

struct State {
	int length, link;
	map<char, int> next;
};

State states[MAXLEN * 2 + 1];
int automataSize, last, cnt[MAXLEN * 2 + 1];

void initialize() {
	automataSize = last = 0;
	states[0].length = 0;
	states[0].link = -1;
	++automataSize;
}

void extend(char c) {
	int current = automataSize++, p;
	cnt[current] = 1;
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

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("search5.in", "r", stdin);
	freopen("search5.out", "w", stdout);
	#endif
	int n;
	scanf("%d\n", &n);
	string t;
	vector<string> p;
	for (int i = 0; i < n; ++i) {
		string s;
		char c;
		scanf("%c", &c);
		while (c != '\n') {
			s += c;
			scanf("%c", &c);
		}
		p.push_back(s);
	}
	initialize();
	char c;
	while (scanf("%c", &c) == 1) {
		extend(c);
	}
	vector<vector<int>> sorted(states[last].length + 1, vector<int>());
	for (int i = 0; i <= last; ++i) {
		sorted[states[i].length].push_back(i);
	}
	for (int i = sorted.size() - 1; i >= 0; --i) {
		for (int j = 0; j < sorted[i].size(); ++j) {
			cnt[states[sorted[i][j]].link] += cnt[sorted[i][j]];
		}
	}
	for (int i = 0; i < p.size(); ++i) {
		int now = 0;
		bool flag = true;
		for (int j = 0; j < p[i].length(); ++j) {
			if (states[now].next.count(p[i][j]) == 1) {
				now = states[now].next[p[i][j]];
			}
			else {
				flag = false;
				break;
			}
		}
		if (flag) {
			printf("%d\n", cnt[now]);
		}
		else {
			printf("0\n");
		}
	}
	return 0;
}