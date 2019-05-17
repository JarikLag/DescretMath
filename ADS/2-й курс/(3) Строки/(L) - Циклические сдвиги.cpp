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
const int alphabet = 255;

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	freopen("shifts.in", "r", stdin);
	freopen("shifts.out", "w", stdout);
	#endif
	string s;
	int n;
	getline(cin, s);
	cin >> n;
	int sizeOfCnt = max(alphabet, (int)s.length()) + 1;
	vector<int> permutation(s.length()), classes(s.length()), cnt(sizeOfCnt, 0);
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
	classes[permutation[0]] = 0;
	for (int i = 1; i < s.length(); ++i) {
		if (s[permutation[i]] != s[permutation[i - 1]]) {
			++numberOfClasses;
		}
		classes[permutation[i]] = numberOfClasses - 1;
	}
	for (int k = 0; (1 << k) < s.length(); ++k) {
		vector<int> currentPermutation(s.length()), currentClasses(s.length());
		for (int i = 0; i < s.length(); ++i) {
			currentPermutation[i] = permutation[i] - (1 << k);
			if (currentPermutation[i] < 0) {
				currentPermutation[i] += s.length();
			}
		}
		cnt.assign(sizeOfCnt, 0);
		for (int i = 0; i < s.length(); ++i) {
			++cnt[classes[currentPermutation[i]]];
		}
		for (int i = 1; i < numberOfClasses; ++i) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = s.length() - 1; i >= 0; --i) {
			permutation[--cnt[classes[currentPermutation[i]]]] = currentPermutation[i];
		}
		currentClasses[permutation[0]] = 0;
		numberOfClasses = 1;
		for (int i = 1; i < s.length(); ++i) {
			int firstPart = (permutation[i] + (1 << k)) % s.length(), secondPart = (permutation[i - 1] + (1 << k)) % s.length();
			if (classes[permutation[i]] != classes[permutation[i - 1]] || classes[firstPart] != classes[secondPart]) {
				++numberOfClasses;
			}
			currentClasses[permutation[i]] = numberOfClasses - 1;
		}
		swap(currentClasses, classes);
	}
	if (numberOfClasses < n) {
		cout << "IMPOSSIBLE";
	}
	else {
		for (int i = 0; i < classes.size(); ++i) {
			if (classes[i] == n - 1) {
				int sz = 0;
				while (sz != s.length()) {
					cout << s[i];
					++i;
					++sz;
					if (i == s.length()) {
						i = 0;
					}
				}
				return 0;
			}
		}
	}
	return 0;
}