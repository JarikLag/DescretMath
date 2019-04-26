#include <cstdio>
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
using namespace std;
 
typedef long long LL;
 
int dp[102][2];
vector<int> used;
 
void calc(vector<vector<int> > g, int v)
{
    if (!used[v])
    {
        if (g[v].size() == 0)
        {
            dp[v][1] = 1;
            return;
        }
        else
        {
            for (int i = 0; i < g[v].size(); i++)
            {
                calc(g, g[v][i]);
                dp[v][1] += dp[g[v][i]][0];
                dp[v][0] += max(dp[g[v][i]][1], dp[g[v][i]][0]);
                used[g[v][i]] = true;
            }
            dp[v][1] += 1;
            used[v] = true;
            return;
        }
    }
}
 
int main()
{
    ios::sync_with_stdio(false);
    //freopen("num2brackets.in", "r", stdin);
    //freopen("num2brackets.out", "w", stdout);
    int n;
    cin >> n;
    int root;
    vector<vector<int> > child(1 + n + 1, vector<int>());
    used.resize(1 + n + 1, false);
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        if (a == 0)
            root = i;
        else
            child[a].push_back(i);
    }
    calc(child, root);
    cout << max(dp[root][0], dp[root][1]);
    return 0;
}