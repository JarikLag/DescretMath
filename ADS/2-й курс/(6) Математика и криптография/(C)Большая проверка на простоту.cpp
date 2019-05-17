#pragma warning(disable : 4996)
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

const LL LONG_INF = 1e18;
const int INT_INF = 1e9 + 7;

LL binaryMul(LL a, LL n, LL m) {
	LL r = 0;
	while (n > 0) {
		if (n & 1 == 1) {
			r = (r + a) % m;
		}
		a = (a + a) % m;
		n >>= 1;
	}
	return r;
}

LL binaryPow(LL a, LL n, LL m) {
	LL res = 1;
	while (n > 0) {
		if ((n & 1) > 0) {
			res = binaryMul(res, a, m);
		}
		a = binaryMul(a, a, m);
		n >>= 1;
	}
	return res;
}

bool ferma(LL val) {
	if (val == 2) {
		return true;
	}
	if (val == 1 || val % 2 == 0) {
		return false;
	}
	srand(time(NULL));
	LL p = 0, q = val - 1;
	while (q % 2 == 0) {
		++p;
		q /= 2;
	}
	for (int i = 0; i < 9; i++) {
		LL a = (rand() % (val - 2)) + 2;
		LL x = binaryPow(a, q, val);
		if (x == 1 || x == val - 1) {
			continue;
		}
		for (int j = 1; j < p; ++j) {
			x = binaryMul(x, x, val);
			if (x == 1) {
				return false;
			}
			if (x == val - 1) {
				break;
			}
		}
		if (x != val - 1) {
			return false;
		}
	}
	return true;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#else
	/*freopen("assignment.in", "r", stdin);
	freopen("assignment.out", "w", stdout);*/
#endif
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		LL x;
		scanf("%lld", &x);
		if (ferma(x)) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
	return 0;
}