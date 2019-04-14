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

using Task = pair<int, int>; //d - w

bool cmp(Task a, Task b) {
	return a.second > b.second;
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("schedule.in", "r", stdin);
	freopen("schedule.out", "w", stdout);
	#endif
	int n;
	LL ans = 0, overall = 0;
	cin >> n;
	vector<Task> tasks(n);
	set<int> times;
	for (int i = 0; i < n; ++i) {
		cin >> tasks[i].first >> tasks[i].second;
		overall += tasks[i].second;
	}
	sort(tasks.begin(), tasks.end(), cmp);
	for (int i = 1; i <= n; ++i) {
		times.insert(i);
	}
	for (int i = 0; i < n; ++i) {
		auto it = times.lower_bound(tasks[i].first);
		if (*it == tasks[i].first) {
			times.erase(it);
			ans += tasks[i].second;
		}
		else if (it == times.begin()) {
			times.erase(--times.end());
		}
		else {
			times.erase(--it);
			ans += tasks[i].second;
		}
	}
	cout << overall - ans;
	return 0;
}