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
const int MAXN = 1e5 + 1;
const int l = 17;
 
vector<int> tree[MAXN];
int time_in[MAXN], time_out[MAXN], up[l][MAXN], depth[MAXN];
int timer = 0;
 
void dfs(int v, int p) {
    time_in[v] = ++timer;
    depth[v] = depth[p] + 1;
    up[0][v] = p;   
    for (int u : tree[v]) {
            dfs(u, v);
    }
    time_out[v] = ++timer;
}
 
bool is_upper(int v, int u) {
    return time_in[v] <= time_in[u] && time_out[u] <= time_out[v];
}
 
int lca(int v, int u) {
    if (is_upper(v, u)) {
        return v;
    }
    if (is_upper(u, v)) {
        return u;
    }
    for (int i = l - 1; i >= 0; --i) {
        if (!is_upper(up[i][v], u)) {
            v = up[i][v];
        }
    }
    return is_upper(v, u) ? v : up[0][v];
}
 
bool cmp(int a, int b) {
    return time_in[a] < time_in[b];
}
 
int main() {
    /*#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #else
    freopen("mail.in", "r", stdin);
    freopen("mail.out", "w", stdout);
    #endif*/
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, root, m;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> up[0][i];
        up[0][i]--;
        if (up[0][i] == -2) {
            up[0][i] = 0;
            root = i;
        }
        else {
            tree[up[0][i]].push_back(i);
        }
    }
    dfs(root, root);
    for (int i = 1; i < l; ++i) {
        for (int v = 0; v < n; ++v) {
            up[i][v] = up[i - 1][up[i - 1][v]];
        }
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        vector<int> groups(k);
        for (int j = 0; j < k; ++j) {
            cin >> groups[j];
            groups[j]--;
        }
        sort(groups.begin(), groups.end(), cmp);
        int ans = depth[groups[0]];
        for (int i = 1; i < groups.size(); ++i) {
            int tmp = lca(groups[i - 1], groups[i]);
            ans += depth[groups[i]] - depth[tmp];
        }
        cout << ans << "\n";
    }
}