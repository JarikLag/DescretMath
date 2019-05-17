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
using namespace std;

typedef long long LL;

const LL INF = 1e18;
const int alphabet = 255;

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("array.in", "r", stdin);
	freopen("array.out", "w", stdout);
	#endif
	string s;
	cin >> s;
	s += "$";
	int sizeOfCnt = max(alphabet, (int)s.length()) + 1;
	int logarithm = floor(log2(s.length()));
	vector<int> permutation(s.length()), cnt(sizeOfCnt, 0);
	vector<vector<int>> classes(logarithm + 2, vector<int>(s.length()));
	int numberOfClasses = 1;
	for (int i = 0; i < s.length(); ++i) {
		++cnt[s[i]];
	}
	for (int i = 1; i < alphabet; ++i) {
		cnt[i] += cnt[i - 1];
	}
	for (int i = 0; i < s.length(); ++i) {
		permutation[--cnt[s[i]]] = i;
	}
	classes[0][permutation[0]] = 0;
	for (int i = 1; i < s.length(); ++i) {
		if (s[permutation[i]] != s[permutation[i - 1]]) {
			++numberOfClasses;
		}
		classes[0][permutation[i]] = numberOfClasses - 1;
	}
	for (int k = 0; (1 << k) < s.length(); ++k) {
		vector<int> currentPermutation(s.length());
		for (int i = 0; i < s.length(); ++i) {
			currentPermutation[i] = permutation[i] - (1 << k);
			if (currentPermutation[i] < 0) {
				currentPermutation[i] += s.length();
			}
		}
		cnt.assign(sizeOfCnt, 0);
		for (int i = 0; i < s.length(); ++i) {
			++cnt[classes[k][currentPermutation[i]]];
		}
		for (int i = 1; i < numberOfClasses; ++i) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = s.length() - 1; i >= 0; --i) {
			permutation[--cnt[classes[k][currentPermutation[i]]]] = currentPermutation[i];
		}
		classes[k + 1][permutation[0]] = 0;
		numberOfClasses = 1;
		for (int i = 1; i < s.length(); ++i) {
			int firstPart = (permutation[i] + (1 << k)) % s.length(), secondPart = (permutation[i - 1] + (1 << k)) % s.length();
			if (classes[k][permutation[i]] != classes[k][permutation[i - 1]] || classes[k][firstPart] != classes[k][secondPart]) {
				++numberOfClasses;
			}
			classes[k + 1][permutation[i]] = numberOfClasses - 1;
		}
	}
	for (int i = 1; i < permutation.size(); ++i) {
		cout << permutation[i] + 1 << ' ';
	}
	cout << endl;
	function<int(int, int)> lcp = [&](int i, int j) {
		int ans = 0;
		for (int k = logarithm; k >= 0; --k) {
			if (classes[k][i] == classes[k][j]) {
				ans += (1 << k);
				i += (1 << k);
				j += (1 << k);
			}
		}
		return ans;
	};
	for (int i = 1; i < permutation.size() - 1; ++i) {
		cout << lcp(permutation[i], permutation[i + 1]) << ' ';
	}
	return 0;
}