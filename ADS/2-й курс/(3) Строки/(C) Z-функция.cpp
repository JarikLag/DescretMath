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
	vector<int> zetaFunc(s.length(), 0);
	int l = 0, r = 0;
	for (int i = 1; i < s.length(); ++i) {
		if (i <= r) {
			zetaFunc[i] = min(r - i + 1, zetaFunc[i - l]);
		}
		while (i + zetaFunc[i] < s.length() 
			&& s[i + zetaFunc[i]] == s[zetaFunc[i]]) {
			++zetaFunc[i];
		}
		if (i + zetaFunc[i] - 1 > r) {
			l = i;
			r = i + zetaFunc[i] - 1;
		}
	}
	for (int i = 1; i < s.length(); ++i) {
		cout << zetaFunc[i] << ' ';
	}
	return 0;
}