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
	vector<int> z(s.length(), 0);
	int l = 0, r = 0;
	for (int i = 1; i < s.length(); ++i) {
		if (i <= r) {
			z[i] = min(r - i + 1, z[i - l]);
		}
		while (i + z[i] < s.length()
			&& s[i + z[i]] == s[z[i]]) {
			++z[i];
		}
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	int period = s.length();
	for (int i = 1; i < s.length(); ++i) {
		if (i + z[i] == s.length() && s.length() % i == 0) {
			period = i;
			break;
		}
	}
	cout << period;
	return 0;
}