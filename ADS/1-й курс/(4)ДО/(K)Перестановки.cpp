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
using namespace std;

typedef long long LL;

const int INF = 1e9;
int sumTree[4 * 100001], hashSumTree[4 * 100001], prefSum[100002], hashSum[100001], prefHashSum[100002], arr[100000];

void build(int v, int l, int r) {
	if (r - l == 1) {
		sumTree[v] = arr[l];
		hashSumTree[v] = hashSum[arr[l]];
		return;
	}
	int m = (r + l) >> 1;
	build(2 * v + 1, l, m);
	build(2 * v + 2, m, r);
	sumTree[v] = sumTree[2 * v + 1] + sumTree[2 * v + 2];
	hashSumTree[v] = hashSumTree[2 * v + 1] + hashSumTree[2 * v + 2];
}

void modify(int v, int l, int r, int pos) {
	if (r - l == 1) {
		sumTree[v] = arr[l];
		hashSumTree[v] = hashSum[arr[l]];
		return;
	}
	int m = (r + l) >> 1;
	if (pos < m) {
		modify(2 * v + 1, l, m, pos);
	}
	else {
		modify(2 * v + 2, m, r, pos);
	}
	sumTree[v] = sumTree[2 * v + 1] + sumTree[2 * v + 2];
	hashSumTree[v] = hashSumTree[2 * v + 1] + hashSumTree[2 * v + 2];
}

void getSum(int v, int l, int r, int from, int to, int &first, int &second) {
	if (l >= to || r <= from)
		return;
	if (l >= from && r <= to) {
		first += sumTree[v];
		second += hashSumTree[v];
		return;
	}
	int m = (r + l) >> 1;
	getSum(2 * v + 1, l, m, from, to, first, second);
	getSum(2 * v + 2, m, r, from, to, first, second);
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	#endif
	int n, m, p = 59;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		prefSum[i + 1] = prefSum[i] + (i + 1);
	}
	scanf("%d", &m);
	for (int i = 1; i <= n; i++) {
		int res = 1, copyI = i, copyP = p;
		while (copyI) {
			if (copyI & 1)
				res *= copyP;
			copyP *= copyP;
			copyI >>= 1;
		}
		hashSum[i] = res;
		prefHashSum[i] = prefHashSum[i - 1] + hashSum[i];
	}
	build(0, 0, n);
	for (int i = 0; i < m; i++) {
		int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		if (t == 1) {
			arr[x - 1] = y;
			modify(0, 0, n, x - 1);
		}
		else {
			int first = 0, second = 0;
			getSum(0, 0, n, x - 1, y, first, second);
			if (first == prefSum[y - x + 1] && second == prefHashSum[y - x + 1]) {
				printf("YES\n");
			}
			else {
				printf("NO\n");
			}
		}
	}
	return 0;
}