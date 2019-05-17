#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <ctime>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <sstream>
#include <stdio.h> 
#include <tuple>
using namespace std;

typedef long long LL;

const LL INF = 1e18;
const int INT_INF = 1e9 + 7;

vector<tuple<int, int, char>> diagonalToAnswer;
vector<vector<int>> graph, modifiedGraph;
vector<vector<char>> matrix;
vector<int> mt;
vector<bool> used;
map<pair<int, int>, pair<int, int>> squareToDiagonals; // (x,y) -> (first type diagonal number, second type diagonal number)
map<pair<int, int>, pair<int, int>> diagonalsToSquare; // (first type diagonal number, second type diagonal number) -> (x,y)
int n, m, diagonalNumber;

bool try_kuhn(int v) {
	if (used[v]) {
		return false;
	}
	used[v] = true;
	for (int i = 0; i < graph[v].size(); ++i) {
		int to = graph[v][i];
		if (mt[to] == -1 || try_kuhn(mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}

void dfs(int v) {
	used[v] = true;
	for (int i = 0; i < modifiedGraph[v].size(); ++i) {
		int to = modifiedGraph[v][i];
		if (!used[to]) {
			dfs(to);
		}
	}
}

char switchColor(char color) {
	if (color == 'W') {
		return 'B';
	}
	else {
		return 'W';
	}
}

vector<tuple<int, int, int, char>> findSolution(char start) {
	char currentColor = start;
	vector<vector<char>> correctMatrix(n, vector<char>(m, '0'));
	diagonalToAnswer.assign(diagonalNumber * 2, tuple<int, int, char>());
	graph.assign(diagonalNumber, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (i != 0 && j == 0) {
				currentColor = switchColor(correctMatrix[i - 1][j]);
			}
			correctMatrix[i][j] = currentColor;
			currentColor = switchColor(correctMatrix[i][j]);
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (correctMatrix[i][j] != matrix[i][j]) {
				pair<int, int> diags = squareToDiagonals[make_pair(i, j)];
				graph[diags.first].push_back(diags.second);
				diagonalToAnswer[diags.first] = make_tuple(i, j, correctMatrix[i][j]);
				diagonalToAnswer[diags.second + diagonalNumber] = make_tuple(i, j, correctMatrix[i][j]);
			}
		}
	}
	mt.assign(diagonalNumber, -1);
	for (int v = 0; v < diagonalNumber; ++v) {
		used.assign(diagonalNumber, false);
		try_kuhn(v);
	}
	modifiedGraph.assign(diagonalNumber * 2, vector<int>());
	vector<bool> isFree(diagonalNumber, true);
	for (int i = 0; i < diagonalNumber; ++i) {
		if (mt[i] != -1) {
			isFree[mt[i]] = false;
		}
	}
	for (int i = 0; i < diagonalNumber; ++i) {
		for (int j = 0; j < graph[i].size(); ++j) {
			if (mt[graph[i][j]] == i) {
				modifiedGraph[graph[i][j] + diagonalNumber].push_back(i);
			}
			else {
				modifiedGraph[i].push_back(graph[i][j] + diagonalNumber);
			}
		}
	}
	used.assign(diagonalNumber * 2, false);
	for (int i = 0; i < diagonalNumber; ++i) {
		if (isFree[i]) {
			dfs(i);
		}
	}
	vector<tuple<int, int, int, char>> answer; //type, (x,y), color
	for (int i = 0; i < diagonalNumber * 2; ++i) {
		int type;
		if (i < diagonalNumber) {
			type = 1;
			if (!used[i]) {				
				answer.push_back(make_tuple(type, get<0>(diagonalToAnswer[i]), get<1>(diagonalToAnswer[i]), get<2>(diagonalToAnswer[i])));
			}
		}
		else {
			type = 2;
			if (used[i]) {
				answer.push_back(make_tuple(type, get<0>(diagonalToAnswer[i]), get<1>(diagonalToAnswer[i]), get<2>(diagonalToAnswer[i])));
			}
		}
	}
	return answer;
}

int main() {
	/*#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	cin >> n >> m;
	matrix.assign(n, vector<char>(m, '0'));
	vector<vector<bool>> usedSquare(n, vector<bool>(m, false));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> matrix[i][j];
		}
	}
	int currentNumber = 0;
	diagonalNumber = n + m - 1;
	for (int i = 0; i < n; ++i) { // first type
		for (int j = 0; j < m; ++j) {
			if (!usedSquare[i][j]) {
				int curI = i, curJ = j;
				while (curI < n && curJ >= 0) {
					usedSquare[curI][curJ] = true;
					squareToDiagonals[make_pair(curI, curJ)].first = currentNumber;
					++curI;
					--curJ;					
				}
				++currentNumber;
			}
		}
	}
	currentNumber = 0;
	usedSquare.assign(n, vector<bool>(m, false));
	for (int i = 0; i < n; ++i) { //second type
		for (int j = m - 1; j >= 0; --j) {
			if (!usedSquare[i][j]) {
				int curI = i, curJ = j;
				while (curI < n && curJ < m) {
					usedSquare[curI][curJ] = true;
					squareToDiagonals[make_pair(curI, curJ)].second = currentNumber;
					++curI;
					++curJ;
				}
				++currentNumber;
			}
		}
	}
	for (auto it : squareToDiagonals) {
		diagonalsToSquare[it.second] = it.first;
	}
	vector<tuple<int, int, int, char>> bAnswer = findSolution('B'), 
		wAnswer = findSolution('W'),
		answer;
	if (bAnswer.size() < wAnswer.size()) {
		answer = bAnswer;
	}
	else {
		answer = wAnswer;
	}
	cout << answer.size() << endl;
	for (int i = 0; i < answer.size(); ++i) {
		cout << get<0>(answer[i]) << ' ' << get<1>(answer[i]) + 1 << ' ' << get<2>(answer[i]) + 1 << ' ' << get<3>(answer[i]) << endl;
	}
	return 0;
}