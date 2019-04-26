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
 
const int INF = 1e9;
 
int graph[15][15], n;
LL dp[1 << 15][15];
bool used[1 << 15][15];
 
LL calc(int mask, int v, int last)
{
    if (dp[mask][v] != 1e18)
        return dp[mask][v];
    for (int u = 0; u <= n; u++)
    {
        if (u != v && u != last)
        {
            if (mask & (1 << u))
            {
                if (used[mask & ~(1 << u)][u])
                {
                    dp[mask][v] = min(dp[mask][v], dp[mask & ~(1 << u)][u] + graph[v][u]);
                }
                else
                {
                    dp[mask][v] = min(dp[mask][v], calc(mask & ~(1 << u), u, v) + graph[v][u]);
                }
            }
        }
    }
    used[mask][v] = true;
    return dp[mask][v];
}
 
int main()
{
    ios::sync_with_stdio(false);
    //freopen("num2brackets.in", "r", stdin);
    //freopen("num2brackets.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> graph[i][j];
        }
    }
    if (n == 1)
    {
        cout << 0 << endl << 1;
        return 0;
    }
    for (int i = 0; i < (1 << (n + 1)); i++)
    {
        for (int j = 0; j <= n; j++)
        {
            dp[i][j] = 1e18;
        }
    }
    dp[0][0] = 0;
    used[0][0] = true;
    calc((1 << (n + 1)) - 1, 0, 0);
    int ind = 0, mask = (1 << (n + 1)) - 1;
    vector<int> path;
    path.push_back(ind);
    while (mask != 0)
    {
        for (int i = 0; i <= n; i++)
        {
            if ((mask & (1 << i)) && (dp[mask][ind] == dp[mask & ~(1 << i)][i] + graph[ind][i]))
            {
                path.push_back(i);
                ind = i;
                mask -= (1 << i);
                continue;
            }
        }
    }
    cout << dp[(1 << (n + 1)) - 1][0] << endl;
    for (int i = 0; i < path.size() - 1; i++)
   