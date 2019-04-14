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
    freopen("shooter.in", "r", stdin);
    freopen("shooter.out", "w", stdout);
    #endif
    cout.precision(13);
    int n, m, k;
    cin >> n >> m >> k;
    vector<double> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i] = pow(1 - p[i], m);
    }
    double ans = p[k - 1], sum = 0;
    for (int i = 0; i < n; i++) {
        sum += p[i];
    }
    ans /= sum;
    cout << ans;
    return 0;
}