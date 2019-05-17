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

int main() {
	string s;
	cin >> s;
	vector<int> prefixFunc(s.length(), 0);
	for (int i = 1; i < s.length(); ++i) {
		int j = prefixFunc[i - 1];
		while (j > 0 && s[i] != s[j]) {
			j = prefixFunc[j - 1];
		}
		if (s[i] == s[j]) {
			++j;
		}
		prefixFunc[i] = j;
	}
	for (int i = 0; i < prefixFunc.size(); ++i) {
		cout << prefixFunc[i] << ' ';
	}
	return 0;
}