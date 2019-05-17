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

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("assignment.in", "r", stdin);
	freopen("assignment.out", "w", stdout);
	#endif
	int n;
	cin >> n;
	vector<vector<int>> a(n + 1, vector<int>(n + 1));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> a[i][j];
		}
	}
	vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
	for (int i = 1; i <= n; ++i) {
		p[0] = i;
		int column = 0;
		vector<int> minv(n + 1, INT_INF);
		vector<char> used(n + 1, false);
		do {
			used[column] = true;
			int row = p[column], delta = INT_INF, index;
			for (int j = 1; j <= n; ++j)
				if (!used[j]) {
					int cur = a[row][j] - u[row] - v[j];
					if (cur < minv[j]) {
						minv[j] = cur;
						way[j] = column;
					}
					if (minv[j] < delta) {
						delta = minv[j];
						index = j;
					}
				}
			for (int j = 0; j <= n; ++j)
				if (used[j]) {
					u[p[j]] += delta;
					v[j] -= delta;
				}
				else {
					minv[j] -= delta;
				}
			column = index;
		} while (p[column] != 0);
		do {
			int index = way[column];
			p[column] = p[index];
			column = index;
		} while (column);
	}
	vector<int> ans(n + 1);
	int sum = 0;
	for (int j = 1; j <= n; ++j) {
		sum += a[p[j]][j];
		ans[p[j]] = j;
	}
	cout << sum << endl;
	for (int i = 1; i <= n; ++i) {
		cout << i << ' ' << ans[i] << endl;
	}
	return 0;
}