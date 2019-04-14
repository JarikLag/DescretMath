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

const int MOD = 998244353;
const int maxWeight = 7;

string combObject;
int position = 0;

LL binomialCoeff(LL n, LL k) {
	double res = 1;
	for (LL i = 1; i <= k; ++i)
		res = res * (n - k + i) / i;
	return (LL)(res + 0.01);
}

vector<LL> calculate() {
	vector<LL> first, second, amount(maxWeight, 0);
	if (combObject[position] == 'B') {
		++position;
		amount[1] = 1;		
	}
	else if (combObject[position] == 'L') {
		position += 2;
		first = calculate();
		++position;
		amount[0] = 1;
		for (int i = 1; i < maxWeight; ++i) {
			LL sum = 0;
			for (int j = 1; j <= i; ++j) {
				sum += amount[i - j] * first[j];
			}
			amount[i] = sum;
		}
	}
	else if (combObject[position] == 'S') {
		position += 2;
		first = calculate();
		++position;
		amount[0] = 1;
		vector<vector<LL>> helper(maxWeight, vector<LL>(maxWeight, 0));
		helper[0][0] = 1;
		for (int i = 1; i < maxWeight; ++i) {
			helper[0][i] = 1;
			helper[i][0] = 0;
		}
		for (int n = 1; n < maxWeight; ++n) {
			for (int k = 1; k < maxWeight; ++k) {
				LL sum = 0;
				for (int i = 0; i <= n / k; ++i) {
					sum += binomialCoeff(first[k] + i - 1, i) * helper[n - i * k][k - 1];
				}
				helper[n][k] = sum;
			}
			amount[n] = helper[n][n];
		}
	}
	else if (combObject[position] == 'P') {
		position += 2;
		first = calculate();
		++position;
		second = calculate();
		++position;
		for (int i = 0; i < maxWeight; ++i) {
			LL sum = 0; 
			for (int j = 0; j <= i; ++j) {
				sum += first[i - j] * second[j];
			}
			amount[i] = sum;
		}
	}
	return amount;
}

int main() {
	#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	getline(cin, combObject);
	vector<LL> answer = calculate();
	for (LL it : answer) {
		cout << it << ' ';
	}
	return 0;
}