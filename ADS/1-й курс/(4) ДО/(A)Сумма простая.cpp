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

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("sum0.in", "r", stdin);
	freopen("sum0.out", "w", stdout);
	#endif

	int n, x, y, a0,
		m, z, t, b0;
	scanf("%d%d%d%d%d%d%d%d", &n, &x, &y, &a0, &m, &z, &t, &b0);
	if (m == 0) {
		printf("0");
		return 0;
	}
	vector<unsigned int> a(n), b(2 * m), c(2 * m);
	vector<LL> pref(n + 1);
	a[0] = a0;
	b[0] = b0;
	c[0] = b[0] % n;
	pref[0] = 0;
	for (int i = 1; i < n; i++) {
		a[i] = (x * a[i - 1] + y) % (1 << 16);
		pref[i] = pref[i - 1] + a[i - 1];
	}
	for (int i = 1; i < m * 2; i++) {
		b[i] = (z * b[i - 1] + t) % (1 << 30);
		c[i] = b[i] % n;
	}
	pref[n] = pref[n - 1] + a[n - 1];
	LL sum = 0;
	for (int i = 0; i < m; i++) {
		int left = min(c[(i * 2)], c[(i * 2) + 1]),
			right = max(c[(i * 2)], c[(i * 2) + 1]);
		sum += (pref[right + 1] - pref[left]);
	}
	printf("%lld", sum);
	return 0;
}