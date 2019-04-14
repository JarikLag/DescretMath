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
using namespace std;
 
typedef long long LL;
 
const int INF = 1e9;

vector<int> lamps;

void calc(int v, int l, int r) {
	if (r == l) {
		lamps.insert(lamps.begin() + l, v);
		return;
	}
	int pos = l + (r - l) / 2;
	string s;
	cout.flush();
	cout << "1 " << lamps[pos] << " " << v << endl;
	cin >> s;
	if (s == "YES") {
		calc(v, pos + 1, r);
	}
	else {
		calc(v, l, pos);
	}
	return;
}

int main() {
    /*#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #else
    freopen("fullham.in", "r", stdin);
    freopen("fullham.out", "w", stdout);
    #endif*/
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		calc(i, 0, lamps.size());
	}
	cout << "0 ";
	for (int i = 0; i < lamps.size(); ++i) {
		cout << lamps[i] << ' ';
	}
	return 0;
}