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
 
vector<vector<pair<int, int>>> tree;
vector<vector<int>> up, mincost;
vector<int> parent_cost, time_in, time_out;
int timer = 0, l;
 
void dfs(int v, int p = 1) {
    time_in[v] = ++timer;
    up[v][0] = p;
    mincost[v][0] = parent_cost[v];
    for (int i = 1; i <= l; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
        if (up[v][i] == up[v][i - 1]) {
            mincost[v][i] = mincost[v][i - 1];
        }
        else {
            mincost[v][i] = min(mincost[v][i - 1], mincost[up[v][i - 1]][i - 1]);
        }
    }
    for (pair<int, int> to : tree[v]) {
        if (to.first != p) {
            dfs(to.first, v);
        }
    }
    time_out[v] = ++timer;
}
 
bool is_upper(int u, int v) {
    return time_in[u] <= time_in[v] && time_out[u] >= time_out[v];
}
 
int min_lca(int u, int v) {
    int a = u, b = v;
    int mini = INF;
    if (is_upper(u, v)) {
        for (int i = l; i >= 0; i--) {
            if (!is_upper(up[b][i], u)) {
                mini = min(mini, mincost[b][i]);
                b = up[b][i];
            }
        }
        mini = min(mini, mincost[b][0]);
        return mini;
    }
    if (is_upper(v, u)) {
        for (int i = l; i >= 0; i--) {
            if (!is_upper(up[a][i], v)) {
                mini = min(mini, mincost[a][i]);
                a = up[a][i];
            }
        }
        mini = min(mini, mincost[a][0]);
        return mini;
    }   
    for (int i = l; i >= 0; i--) {
        if (!is_upper(up[a][i], v)) {
            mini = min(mini, mincost[a][i]);
            a = up[a][i];
        }
    }
    mini = min(mini, mincost[a][0]);
    for (int i = l; i >= 0; i--) {
        if (!is_upper(up[b][i], u)) {
            mini = min(mini, mincost[b][i]);
            b = up[b][i];           
        }
    }
    mini = min(mini, mincost[b][0]);
    return mini;
}
 
int main() {
    #ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #else
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
    #endif
    int n, m;
    scanf("%d", &n);
    l = ceil(log2(n));
    tree.resize(n + 1);
    up.resize(n + 1);
    parent_cost.resize(n + 1);
    time_in.resize(n + 1);
    time_out.resize(n + 1);
    mincost.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        up[i].resize(l + 1);
        mincost[i].resize(l + 1, INF);
 
    }
    for (int i = 2; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        parent_cost[i] = y;
        tree[x].push_back(make_pair(i, y));
    }
    dfs(1);
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", min_lca(u, v));       
    }
    return 0;
}