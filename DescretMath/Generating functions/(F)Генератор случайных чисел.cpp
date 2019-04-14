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

const int MOD = 104857601;

void check(LL& x) {
	while (x < 0) {
		x = (x + MOD) % MOD;
	}
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	int k;
	LL n;
	cin >> k >> n;
	vector<LL> initValues(2 * k, 0), polynomial(k + 1, 0);
	for (int i = 0; i < k; ++i) {
		cin >> initValues[i];
	}
	--n;
	polynomial[0] = 1;
	for (int i = 1; i <= k; ++i) {
		cin >> polynomial[i];
		polynomial[i] = (-polynomial[i] + MOD) % MOD;
		check(polynomial[i]);
	}
	while (n >= k) {
		for (int i = k; i < 2 * k; ++i) {
			LL sum = 0;
			for (int j = 1; j <= k; ++j) {
				sum = (sum - polynomial[j] * initValues[i - j] + MOD) % MOD;
				check(sum);
			}
			initValues[i] = sum;
		}
		vector<LL> rPolynomial(k + 1);
		for (int i = 0; i <= 2 * k; i += 2) {
			LL sum = 0;
			for (int j = 0; j <= i; ++j) {
				LL q = 0, negQ = 0;
				if (j <= k) {
					q = polynomial[j];
				}
				if (i - j <= k) {
					if ((i - j) % 2 == 0) {
						negQ = polynomial[i - j];
					}
					else {
						negQ = (-polynomial[i - j] + MOD) % MOD;
						check(negQ);
					}
				}
				sum = (sum + q * negQ + MOD) % MOD;
			}
			rPolynomial[i / 2] = sum;
		}		
		int it = 0;
		for (int i = 0; i < 2 * k; ++i) {
			if (i % 2 == n % 2) {
				initValues[it] = initValues[i];
				++it;
			}
		}
		for (int i = 0; i <= k; i++) {
			polynomial[i] = rPolynomial[i];
		}
		n /= 2;
	}
	cout << initValues[n];
	return 0;
}