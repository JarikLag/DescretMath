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

//1v->0, 2v->1, 3v->3, 4v->6, 5v->10, 6v->15 

vector<vector<int>> graph;

string myAnd(const string& s1, const string& s2) {
	string res;
	for (int i = 0; i < s1.size(); ++i) {
		if (s1[i] == '1' && s2[i] == '1') {
			res += '1';
		}
		else {
			res += '0';
		}
	}
	return res;
}

void makeGraph(const string& s, int size) {
	graph.assign(size, vector<int>());
	int index = 0;
	for (int i = 0; i < size - 1; ++i) {
		for (int j = 0; j < i + 1; ++j) {
			if (s[index] == '1') {
				graph[i + 1].push_back(j);
				graph[j].push_back(i + 1);
			}
			++index;
		}
	}
}

bool checkBigraph(const string& s) {
	vector<string> bigraphs = { "000111111011100", "011001110111010", "101010101110110", "110100011101110", "011110001111001",
		"101101010110101", "110011100101101", "110011011010011", "101101101001011", "011110110000111" };
	for (int i = 0; i < bigraphs.size(); ++i) {
		if (myAnd(s, bigraphs[i]) == bigraphs[i]) {
			return true;
		}
	}
	return false;
}

bool checkFullGraph(int ind) {
	vector<vector<int>> ngraph(graph);
	for (int i = 0; i < ngraph.size(); ++i) {
		if (i == ind)
			continue;
		auto it = find(ngraph[i].begin(), ngraph[i].end(), ind);
		if (it != ngraph[i].end()) {
			ngraph[i].erase(it);
		}
	}
	bool isFull = true;
	for (int i = 0; i < ngraph.size(); ++i) {
		if (i == ind)
			continue;
		if (ngraph[i].size() < 4) {
			isFull = false;
			break;
		}
	}
	if (isFull) {
		return true;
	}
	int f = -1, s = -1, cnt = 0;
	for (int i = 0; i < ngraph.size(); ++i) {
		if (i == ind)
			continue;
		if (ngraph[i].size() < 4) {
			++cnt;
			if (ngraph[i].size() == 3) {
				if (f == -1) {
					f = i;
				}
				else if (s == -1) {
					s = i;
				}
			}
		}
	}
	if (cnt != 2 || (f == -1 || s == -1)) {
		return false;
	}
	if ((find(graph[ind].begin(), graph[ind].end(), f) != graph[ind].end())
		&& (find(graph[ind].begin(), graph[ind].end(), s) != graph[ind].end())) {
		return true;
	}
	return false;
}

bool checkPlanarity(const string& s) {
	if (s.length() < 10) {
		return true;
	}
	if (s.length() == 10) {
		for (int i = 0; i < s.length(); ++i) {
			if (s[i] == '0') {
				return true;
			}
		}
		return false;
	}
	if (s.length() == 15) {
		makeGraph(s, 6);
		if (checkBigraph(s)) {
			return false;
		}
		for (int i = 0; i < 6; ++i) {
			if (checkFullGraph(i)) {
				return false;
			}
		}
		return true;
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("planaritycheck.in", "r", stdin);
	freopen("planaritycheck.out", "w", stdout);
	#endif
	int n;
	cin >> n;
	string s;
	getline(cin, s);
	vector<string> tests(n);
	for (int i = 0; i < n; ++i) {
		getline(cin, s);
		tests[i] = s;
	}
	for (int i = 0; i < n; ++i) {
		graph.clear();
		if (checkPlanarity(tests[i])) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}