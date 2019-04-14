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

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("epsilon.in", "r", stdin);
	freopen("epsilon.out", "w", stdout);
	#endif
	int n;
	char start;
	scanf("%d %c\n", &n, &start);
	map<char, vector<string>> arr;
	map<char, bool> is_epsilon;
	for (int i = 0; i < n; ++i) {
		string s, to;
		getline(cin, s);
		if (s.length() != 4) {
			to = s.substr(5);
		}
		arr[s[0]].push_back(to);
	}
	for (auto now : arr) {
		for (string str : now.second) {
			bool flag = true;
			for (int i = 0; i < str.length(); ++i) {
				if (((str[i] <= 'Z' && str[i] >= 'A') && is_epsilon[str[i]] == false) || (str[i] <= 'z' && str[i] >= 'a')) {
					flag = false;
					break;
				}
			}
			if (flag) {
				is_epsilon[now.first] = true;
			}
		}
	}
	int changed;
	do {
		changed = 0;
		for (auto now : arr) {
			if (!is_epsilon[now.first]) {
				for (string str : now.second) {
					bool flag = true;
					for (int i = 0; i < str.length(); ++i) {
						if (((str[i] <= 'Z' && str[i] >= 'A') && is_epsilon[str[i]] == false) || (str[i] <= 'z' && str[i] >= 'a')) {
							flag = false;
							break;
						}
					}
					if (flag) {
						++changed;
						is_epsilon[now.first] = true;
					}
				}
			}
		}
	} while (changed);
	vector<char> ans;
	for (auto now : arr) {
		if (is_epsilon[now.first]) {
			ans.push_back(now.first);
		}
	}
	for (int i = 0; i < ans.size(); ++i) {
		cout << ans[i];
		if (i != ans.size() - 1) {
			cout << ' ';
		}
	}
	return 0;
}