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
    freopen("lottery.in", "r", stdin);
    freopen("lottery.out", "w", stdout);
    #endif
    cout.precision(9);
    int n, m;
    double winP = 0, winM = 0;
    cin >> n >> m;
    vector<pair<double, double>> vect;
    for (int i = 0; i < m; i++) {
        double a, b;
        cin >> a >> b;
        vect.push_back(make_pair(a, b));
    }
    winP += (1 / vect[0].first);
    for (int i = 0; i < m - 1; i++) {
        winM += (winP * (1 - (1 / vect[i + 1].first))) * vect[i].second;
        winP *= (1 / vect[i + 1].first);
    }
    winM += (winP * vect[m - 1].second);
    winM = double(n) - winM;
    cout << winM;
    return 0;
}