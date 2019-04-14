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
	freopen("cycles.in", "r", stdin);
	freopen("cycles.out", "w", stdout);
	#endif
	int n, s, answer = 0;
	cin >> n >> s;
	vector<int> weight(n), sets(s);
	for (int i = 0; i < n; ++i) {
		cin >> weight[i];
	}
	for (int i = 0; i < s; ++i) {
		int sz, now = 0, a;
		cin >> sz;
		for (int j = 0; j < sz; ++j) {
			cin >> a;
			now |= (1 << (a - 1));
		}
		sets[i] = now;
	}
	for (int i = 1; i < (1 << n); ++i) {
		bool flag = true;
		for (int j = 0; j < s; ++j) {
			if ((i & sets[j]) == sets[j]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			string binary = bitset<20>(i).to_string();
			reverse(binary.begin(), binary.end());
			int cur = 0;
			for (int k = n - 1; k >= 0; --k) {
				cur += (binary[k] - '0') * weight[k];
			}
			answer = max(answer, cur);
		}
	}
	cout << answer;
	return 0;
}