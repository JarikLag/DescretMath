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
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("check.in", "r", stdin);
	freopen("check.out", "w", stdout);
	#endif
	int n, p = 97;
	string s;
	cin >> s >> n;
	vector<LL> power(s.length() + 1, 1), hash(s.length() + 1);
	for (int i = 1; i < s.length(); ++i) {
		power[i] = power[i - 1] * p;
	}
	for (int i = 0; i < s.length(); ++i) {
		hash[i] = (s[i] - '0') * power[i];
		if (i > 0) {
			hash[i] += hash[i - 1];
		}
	}
	for (int i = 0; i < n; ++i) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		--a, --b, --c, --d;
		if (b - a != d - c) {
			cout << "No" << endl;
			continue;
		}
		LL h1 = hash[b];
		if (a > 0) {
			h1 -= hash[a - 1];
		}
		LL h2 = hash[d];
		if (c > 0) {
			h2 -= hash[c - 1];
		}
		if (a <= c && h1 * power[c - a] == h2
			|| a > c && h2 * power[a - c] == h1) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}
	return 0;
}