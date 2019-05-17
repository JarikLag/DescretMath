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
const int alf = 28;

struct Vertex {
	int next[alf], autoMove[alf];
	int link, fastLink;
	vector<int> patternIndexes;
	int parent;
	bool leaf;
	char symbol;
};

vector<Vertex> trie;
vector<string> patterns, strings;
vector<int> firstPositions, positions;

Vertex addVertex(int p, char c) {
	Vertex v;
	memset(v.next, 255, sizeof(v.next));
	memset(v.autoMove, 255, sizeof(v.autoMove));
	v.leaf = false;
	v.link = -1;
	v.parent = p;
	v.symbol = c;
	v.fastLink = -1;
	return v;
}

void initialize() {
	trie.push_back(addVertex(0, '$'));
}

void addString(const string& s) {
	int v = 0;
	for (int i = 0; i < s.length(); ++i) {
		char ch = s[i] - 'a';
		if (trie[v].next[ch] == -1) {
			trie.push_back(addVertex(v, ch));
			trie[v].next[ch] = trie.size() - 1;
		}
		v = trie[v].next[ch];
	}
	trie[v].leaf = true;
	patterns.push_back(s);
	trie[v].patternIndexes.push_back(patterns.size() - 1);
}

void addStringRev(const string& s, int i) {
	int v = 0;
	for (int i = s.length() - 1; i >= 0; --i) {
		char ch = s[i] - 'a';
		if (trie[v].next[ch] == -1) {
			trie.push_back(addVertex(v, ch));
			trie[v].next[ch] = trie.size() - 1;
		}
		v = trie[v].next[ch];
	}
	trie[v].leaf = true;
	trie[v].patternIndexes.push_back(i);
}

int go(int v, char ch);

int getLink(int v) {
	if (trie[v].link == -1) {
		if (v == 0 || trie[v].parent == 0) {
			trie[v].link = 0;
		}
		else {
			trie[v].link = go(getLink(trie[v].parent), trie[v].symbol);
		}
	}
	return trie[v].link;
}

int go(int v, char ch) {
	if (trie[v].autoMove[ch] == -1) {
		if (trie[v].next[ch] != -1) {
			trie[v].autoMove[ch] = trie[v].next[ch];
		}
		else {
			if (v == 0) {
				trie[v].autoMove[ch] = 0;
			}
			else {
				trie[v].autoMove[ch] = go(getLink(v), ch);
			}
		}
	}
	return trie[v].autoMove[ch];
}

int getFastLink(int v) {
	if (trie[v].fastLink == -1) {
		int u = getLink(v);
		if (u == 0) {
			trie[v].fastLink = 0;
		}
		else {
			trie[v].fastLink = (trie[u].leaf) ? u : getFastLink(u);
		}
	}
	return trie[v].fastLink;
}

void check(int v, int i) {
	for (int u = v; u != 0; u = getFastLink(u)) {
		if (trie[u].leaf) {
			while (trie[u].patternIndexes.size() > 0) {
				positions[trie[u].patternIndexes.back()] = i - patterns[trie[u].patternIndexes.back()].length();
				trie[u].patternIndexes.pop_back();
			}
			trie[u].leaf = false;
		}
	}
}

void findFirstPositions(const string& s) {
	int u = 0;
	for (int i = 0; i < s.length(); ++i) {
		u = go(u, s[i] - 'a');
		check(u, i + 1);
	}
}

void findFirstPositionsRev(const string& s) {
	int u = 0;
	for (int i = s.length() - 1; i >= 0; --i) {
		u = go(u, s[i] - 'a');
		check(u, s.length() - i);
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("search6.in", "r", stdin);
	freopen("search6.out", "w", stdout);
	#endif
	int n;
	scanf("%d\n", &n);
	firstPositions.assign(n, -1);
	positions.assign(n, -1);
	initialize();
	string t;
	char c;
	for (int i = 0; i < n; ++i) {
		string s;		
		scanf("%c", &c);
		while (c != '\n') {
			s += c;
			scanf("%c", &c);
		}
		strings.push_back(s);
		addString(s);
	}
	while (scanf("%c", &c) == 1 && c != '\n') {
		t += c;
	}
	findFirstPositions(t);
	swap(positions, firstPositions);
	trie.clear();
	initialize();
	for (int i = 0; i < n; ++i) {
		addStringRev(strings[i], i);
	}
	findFirstPositionsRev(t);
	for (int i = 0; i < n; ++i) {
		printf("%d ", firstPositions[i]);
		if (positions[i] == -1) {
			printf("-1\n");
		}
		else {
			printf("%d\n", t.length() - positions[i] - patterns[i].length());
		}
	}
	return 0;
}