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
	freopen("sparse.in", "r", stdin);
	freopen("sparse.out", "w", stdout);
	#endif
	int n, m;
	cin >> n >> m;
	vector <vector <int> > a(n, vector <int>(20, 0));

	int u, v, ans;
	cin >> a[0][0] >> u >> v;

	for (int j = 1; j < 20; j++)
		a[0][j] = a[0][j - 1];
	for (int i = 1; i < n; i++) {
		a[i][0] = (a[i - 1][0] * 23 + 21563) % 16714589;
		int j;
		for (j = 1; i - (1 << (j - 1)) >= 0; j++) {
			a[i][j] = min(a[i][j - 1], a[i - (1 << (j - 1))][j - 1]);
		}
		for (; j < 20; j++) {
			a[i][j] = a[i][j - 1];
		}
	}

	int nu, nv;
	for (int i = 0; i < m; i++) {
		nu = min(u, v) - 1;
		nv = max(u, v) - 1;

		int len = nv - nu + 1;
		int j = log2(len);
		ans = min(a[nv][j], a[nu + (1 << j) - 1][j]);

		nu = ((17 * u + 753 + ans + 2 * i) % n) + 1;
		nv = ((13 * v + 598 + ans + 5 * i) % n) + 1;
		swap(u, nu);
		swap(v, nv);
	}

	cout << nu << " " << nv << " " << ans;
	return 0;
}