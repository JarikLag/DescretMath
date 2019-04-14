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
    freopen("exam.in", "r", stdin);
    freopen("exam.out", "w", stdout);
    #endif
    cout.precision(5);
    int k, n;
    cin >> k >> n;
    double ans = 0;
    for (int i = 0; i < k; i++) {
        double a, b;
        cin >> a >> b;
        double now = a / n;
        ans += (now * b) / 100;
    }
    cout << ans;
    return 0;
}