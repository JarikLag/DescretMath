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
const int MAXN = 1e5 + 2;
 
 
int time_in[MAXN], time_out[MAXN];
int l = 18, timer = 0;
 
bool cmp(int a, int b) {
    return time_in[a] < time_in[b];
}
 
vector<int> depth, ffirst, mass, mass_d;
vector<vector<int>> g;
vector<vector<int>> st, iind;
 
void dfs(int v, int p) {
    time_in[v] = ++timer;
    mass.push_back(v);
    mass_d.push_back(depth[v]);
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        depth[to] = depth[v] + 1;
        dfs(to, v);
        mass.push_back(v);
        mass_d.push_back(depth[v]);
    }
    time_out[v] = ++timer;
}
 
void calc(vector<int> &v) {
    int n = v.size();
    int nn = ceil(log2(n));
    if (n == 1) {
        nn = 1;
    }
    st.assign(nn, vector<int>(n, INF));
    iind.assign(nn, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        st[0][i] = v[i];
        iind[0][i] = i;
    }
    for (int i = 1; i < nn; ++i) {
        for (int j = 0; j + (1 << (i - 1)) < n; ++j) {
            if (st[i - 1][j] < st[i - 1][j + (1 << (i - 1))]) {
                iind[i][j] = iind[i - 1][j];
            }
            else {
                iind[i][j] = iind[i - 1][j + (1 << (i - 1))];
            }
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
}
 
int get_min(int a, int b) {
    int l = ffirst[a], r = ffirst[b];
    if (l > r) {
        swap(l, r);
    }
    int lg = log2(r - l + 1), len = (1 << lg);
    if (st[lg][l] < st[lg][r - len + 1]) {
        return mass[iind[lg][l]];
    }
    else {
        return mass[iind[lg][r - len + 1]];
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    /*#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #else
    freopen("mail.in", "r", stdin);
    freopen("mail.out", "w", stdout);
    #endif*/
    int n, m;
    int root;
    cin >> n;
    g.resize(n + 1);
    depth.resize(n + 1, 0);
    ffirst.resize(n + 1, INF);
    for (int i = 1; i <= n; ++i) {
        int v;
        cin >> v;
        if (v == -1) {
            root = i;
        }
        else {
            g[v].push_back(i);
        }
    }
    depth[root] = 1;
    dfs(root, root);
    for (int i = 0; i < mass.size(); ++i) {
        ffirst[mass[i]] = min(ffirst[mass[i]], i);
    }
    calc(mass_d);
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int k, ans = 0;
        vector<int> tmp;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v;
            tmp.push_back(v);
        }
        sort(tmp.begin(), tmp.end(), cmp);
        for (int j = 0; j < k; ++j) {
            ans += depth[tmp[j]];
            if (j == 0) {
                continue;
            }
            ans -= depth[get_min(tmp[j], tmp[j - 1])];
        }
        cout << ans << "\n";
    }
    return 0;
}