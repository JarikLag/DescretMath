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

const int INF = 1e9;

vector<vector<int>> graph, invertedGraph;
vector<bool> used;
vector<int> order, component;
map<string, int> nameToNumber;
map<int, string> numberToName;
vector<bool> invites;
int componentNumber = 0;

void dfs1(int v) {
	used[v] = true;
	for (int i = 0; i < graph[v].size(); ++i) {
		if (!used[graph[v][i]]) {
			dfs1(graph[v][i]);
		}
	}
	order.push_back(v);
}

void dfs2(int v) {
	used[v] = true;
	for (int i = 0; i < invertedGraph[v].size(); ++i) {
		if (!used[invertedGraph[v][i]]) {
			dfs2(invertedGraph[v][i]);
		}
	}
	component[v] = componentNumber;
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	/*#else
	freopen("epsilon.in", "r", stdin);
	freopen("epsilon.out", "w", stdout);*/
	#endif
	int n, m, nowNum = 0; //нечётные - x, чётные - !x
	cin >> n >> m;
	graph.resize(2 * (n + 1));
	invertedGraph.resize(2 * (n + 1));
	component.resize(2 * (n + 1));
	invites.resize(2 * (n + 1));
	string buff;
	for (int i = 0; i < n; ++i) {
		cin >> buff;
	}
	for (int i = 0; i < m; ++i) {
		string name1, name2, arrow, notName1, notName2;
		cin >> name1 >> arrow >> name2;
		notName1 = name1;
		notName2 = name2;
		if (name1[0] == '-') {			
			notName1[0] = '+';
		}
		else {
			notName1[0] = '-';
		}
		if (name2[0] == '-') {
			notName2[0] = '+';
		}
		else {
			notName2[0] = '-';
		}
		if (nameToNumber[name1] == 0) {
			++nowNum;
			nameToNumber[name1] = nowNum;
			numberToName[nowNum] = name1;
		}
		if (nameToNumber[notName1] == 0) {
			++nowNum;
			nameToNumber[notName1] = nowNum;
			numberToName[nowNum] = notName1;
		}
		if (nameToNumber[name2] == 0) {
			++nowNum;
			nameToNumber[name2] = nowNum;
			numberToName[nowNum] = name2;
		}
		if (nameToNumber[notName2] == 0) {
			++nowNum;
			nameToNumber[notName2] = nowNum;
			numberToName[nowNum] = notName2;
		}
		graph[nameToNumber[name1]].push_back(nameToNumber[name2]);
		graph[nameToNumber[notName2]].push_back(nameToNumber[notName1]);
		invertedGraph[nameToNumber[name2]].push_back(nameToNumber[name1]);
		invertedGraph[nameToNumber[notName1]].push_back(nameToNumber[notName2]);
	}
	used.resize(2 * (n + 1), false);
	for (int i = 1; i <= 2 * n; ++i) {
		if (!used[i]) {
			dfs1(i);
		}
	}
	used.assign(2 * (n + 1), false);
	for (int i = 0; i < 2 * n; ++i) {
		int v = order[2 * n - i - 1];
		if (!used[v]) {
			componentNumber++;
			dfs2(v);
		}
	}
	for (int i = 1; i <= 2 * n; i += 2) {
		if (component[i] == component[i + 1]) {
			cout << -1;
			return 0;
		}
	}
	for (int i = 1; i <= 2 * n; i += 2) {
		if (component[i] > component[i + 1]) {
			invites[i] = true;
			invites[i + 1] = false;
		}
		else {
			invites[i] = false;
			invites[i + 1] = true;
		}
	}
	set<string> list;
	for (int i = 1; i <= 2 * n; ++i) {
		if ((numberToName[i][0] == '+' && invites[i]) || (numberToName[i][0] == '-' && !invites[i])) {
			string tmp = numberToName[i].substr(1);
			list.insert(tmp);
		}
	}
	cout << list.size() << endl;
	for (auto it = list.begin(); it != list.end(); ++it) {
		cout << *it << endl;
	}
	return 0;
}