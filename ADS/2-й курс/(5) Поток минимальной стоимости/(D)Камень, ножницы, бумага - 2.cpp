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
	freopen("rps2.in", "r", stdin);
	freopen("rps2.out", "w", stdout);
	#endif
	int r1, s1, p1, r2, s2, p2;
	cin >> r1 >> s1 >> p1 >> r2 >> s2 >> p2;
	cout << max(0, (max(r1 - r2 - p2, max(s1 - s2 - r2, p1 - p2 - s2))));
	return 0;
}