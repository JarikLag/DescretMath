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
using namespace std;

typedef long long LL;

vector<LL> arr, fenwick;

void init() {
	for (int i = 0; i < int(fenwick.size()); i++) {
		int j = i | (i + 1);
		if (j < int(fenwick.size())) {
			fenwick[j] += fenwick[i];
		}
	}
}

void add(int i, LL x) {
	for (; i < int(fenwick.size()); i = i | (i + 1)) {
		fenwick[i] += x;
	}
}

LL prefSum(LL x) {
	LL ans = 0;
	for (; x >= 0; x = (x & (x + 1)) - 1)
		ans += fenwick[x];
	return ans;
}

LL segSum(int l, int r) {
	return prefSum(r) - prefSum(l - 1);
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("rsq.in", "r", stdin);
	freopen("rsq.out", "w", stdout);
	#endif
	
	int n;
	cin >> n;
	arr.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	fenwick = arr;
	init();
	string s;
	while (cin >> s) {
		LL x, y;
		cin >> x >> y;
		if (s == "sum") {
			cout << segSum(x - 1, y - 1) << endl;
		}
		else {
			add(x - 1, y - arr[x - 1]);
			arr[x - 1] = y;
		}
	}
	return 0;
}