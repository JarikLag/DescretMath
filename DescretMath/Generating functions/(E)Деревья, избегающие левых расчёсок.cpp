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
 
void check(LL& x) {
    while (x < 0) {
        x = (x + MOD);
    }
}
 
LL getElement(const vector<LL>& pol, const int ind) {
    if (ind >= pol.size() || ind < 0) {
        return 0;
    }
    else {
        return pol[ind];
    }
}
 
int main() {
    #ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int n, k;
    cin >> k >> n;
    vector<vector<LL>> binomialCoeff(k + 1, vector<LL>(k + 1, 0));
    vector<LL> p(ceil(double((k - 1) / 2.))), q(ceil(double(k / 2.)));
    for (int i = 0; i <= k; ++i) {
        binomialCoeff[i][0] = binomialCoeff[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            binomialCoeff[i][j] = (binomialCoeff[i - 1][j - 1] + binomialCoeff[i - 1][j]) % MOD;
        }
    }
    for (int i = 0; i < p.size(); ++i) {
        p[i] = binomialCoeff[k - i - 2][i] * (pow(-1, i));
    }
    for (int i = 0; i < q.size(); ++i) {
        q[i] = binomialCoeff[k - i - 1][i] * (pow(-1, i));
    }
    vector<LL> coefficient(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        LL cur = getElement(p, i);
        for (int j = 0; j <= i; ++j) {
            cur = (cur - (coefficient[i - j] * getElement(q, j)) % MOD + MOD) % MOD;
        }   
        check(cur);
        coefficient[i] = cur;
        cout << coefficient[i] << '\n';
    }
    return 0;
}