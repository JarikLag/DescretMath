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
 
int main() {
    #ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #else
    freopen("guyaury.in", "r", stdin);
    freopen("guyaury.out", "w", stdout);
    #endif
    int n;
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n, 0));
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < i + 1; ++j) {
            char c;
            cin >> c;
            if (c == '1') {
                graph[i + 1][j] = 1;
            }
            else {
                graph[j][i + 1] = 1;
            }
        }
    }
    vector<int> path;
    for (int i = 0; i < n; ++i) {
        int k = 0;
        for (int j = 0; j < path.size(); ++j) {
            if (graph[path[j]][i] == 1) {
                ++k;
            }
            else {
                break;
            }
        }
        path.insert(path.begin() + k, i);
    }
    vector<int> circuit;
    for (int i = 1; i < (int)path.size(); ++i) {
        int prev = path[i - 1], curr = path[i];
        if (graph[prev][curr] == 0) {
            return 1;
        }
    }
    int start = path[0], k;
    for (k = path.size() - 1; k >= 2; --k) {
        if (graph[path[k]][start] == 1) {
            break;
        }
    }
    circuit.insert(circuit.begin(), path.begin(), path.begin() + k + 1);
    path.erase(path.begin(), path.begin() + k + 1);
    for (auto st = path.begin(); st != path.end(); ) {
        auto it = circuit.begin();
        while (it != circuit.end() && graph[*it][*st]) {
            ++it;
        }
        if (it != circuit.end()) {
            circuit.insert(it, path.begin(), st + 1);
            path.erase(path.begin(), st + 1);
            st = path.begin();
        }
        else {
            ++st;
        }
    }
    for (int i = 0; i < circuit.size(); ++i) {
        cout << circuit[i] + 1 << ' ';
    }
    return 0;
}