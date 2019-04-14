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
    freopen("markchain.in", "r", stdin);
    freopen("markchain.out", "w", stdout);
    #endif
    cout.precision(7);
    int n;
    cin >> n;
    vector<vector<double> > matrix(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    double eps = 1e-5;
    while (1) {     
        vector<vector<double> > res(n, vector<double>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    res[i][j] += matrix[i][k] * matrix[k][j];
                }
            }
        }
        double maxDiff = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                maxDiff = max(maxDiff, abs(matrix[i][j] - res[i][j]));
            }
        }
        if (maxDiff < eps) {
            for (int i = 0; i < n; i++) {
                cout << fixed << res[i][i] << endl;
            }
            break;
        }
        else {
            matrix = res;
        }
    }   
    return 0;
}