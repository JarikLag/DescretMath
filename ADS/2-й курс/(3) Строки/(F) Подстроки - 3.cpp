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
	int specialSymbolPath = 0;
	int backVertex = -1;
	char backChar = '0';
	map<char, int> next;
};

State states[MAXLEN * 2 + 1];
vector<bool> used(MAXLEN * 2 + 1, false);
int automataSize, last, idealPath = 0, maxLength = -1, maxState = -1;
string answer;

void initialize() {
	automataSize = last = 0;
	states[0].length = 0;
	states[0].link = -1;
	++automataSize;
}

void extend(char c) {
	int current = automataSize++, p;
	states[current].length = states[last].length + 1;
	states[current].backChar = c;
	states[current].backVertex = last;
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
			states[clone].backChar = states[q].backChar;
			states[clone].backVertex = states[q].backVertex;
			for (; p != -1 && states[p].next[c] == q; p = states[p].link)
				states[p].next[c] = clone;
			states[q].link = states[current].link = clone;
		}
	}
	last = current;
}

void calculatePath(int v) {
	if (used[v]) {
		return;
	}
	used[v] = true;
	for (auto it : states[v].next) {
		if (it.first >= '0' && it.first <= '9') {
			states[v].specialSymbolPath |= (1 << (it.first - '0'));
		}
		else {
			calculatePath(it.second);
			states[v].specialSymbolPath |= states[it.second].specialSymbolPath;
		}
	}
	if (states[v].specialSymbolPath == idealPath) {
		if (maxLength < states[v].length) {
			maxLength = states[v].length;
			maxState = v;
		}
	}
}

void restoreString(int v, int len) {
	if (len == 0) {
		return;
	}
	answer += states[v].backChar;
	restoreString(states[v].backVertex, len - 1);
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	/*freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);*/
	#endif
	int n;
	char c;
	scanf("%d\n", &n);
	initialize();
	for (int i = 0; i < n; ++i) {
		idealPath |= (1 << i);
		while (scanf("%c", &c) == 1 && c != '\n') {
			extend(c);
		}
		extend(i + '0');
	}
	calculatePath(0);
	restoreString(maxState, maxLength);
	for (int i = answer.length() - 1; i >= 0; --i) {
		printf("%c", answer[i]);
	}
	return 0;
}