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
const int MAXLEN = 100000;

struct State {
	int length, link;
	map<char, int> next;
};

State states[MAXLEN * 2 + 1];
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

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("common.in", "r", stdin);
	freopen("common.out", "w", stdout);
	#endif
	int n;
	scanf("%d\n", &n);
	string s, t;
	char c;
	scanf("%c", &c);
	while (c != '\n') {
		s += c;
		scanf("%c", &c);
	}
	initialize();
	while (scanf("%c", &c) == 1) {
		t += c;
		extend(c);
	}
	int v = 0, l = 0, best = 0, bestPosition = 0;
	for (int i = 0; i < s.length(); ++i) {
		while (v && !states[v].next.count(s[i])) {
			v = states[v].link;
			l = states[v].length;
		}
		if (states[v].next.count(s[i])) {
			v = states[v].next[s[i]];
			++l;
		}
		if (l >= best) {
			if (l == best) {
				if (s[bestPosition - best + 1] > s[i - l + 1]) {
					best = l;
					bestPosition = i;
				}
			}
			else {
				best = l;
				bestPosition = i;
			}
		}
	}
	cout << s.substr(bestPosition - best + 1, best);
	return 0;
}