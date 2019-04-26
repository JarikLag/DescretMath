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
 
int main()
{
    ios::sync_with_stdio(false);
    //freopen("skyscraper.in", "r", stdin);
    //freopen("skyscraper.out", "w", stdout);
    int n, arr[101], dp[103][103], p[103][103];
    int ans = 2 * INF, k1 = -1, k2 = -1;
    cin >> n;
    if (n == 0)
    {
        cout << 0 << endl << 0 << ' ' << 0 << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    if (n == 1)
    {
        if (arr[1] > 100)
        {
            cout << arr[1] << endl << 1 << ' ' << 0;
            return 0;
        }
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            dp[i][j] = INF;
            p[i][j] = 0;
        }
    }
    dp[0][0] = 0;
    map<pair<int, int>, vector<int> > omg;
    for (int d = 1; d <= n; d++)
    {
        for (int c = 0; c < n; c++)
        {
            if (arr[d] > 100)
            {
                if (c > 0)
                {
                    if (dp[d - 1][c - 1] + arr[d] < dp[d - 1][c + 1])
                    {
                        dp[d][c] = dp[d - 1][c - 1] + arr[d];
                        p[d][c] = p[d - 1][c - 1] + 1;
                        omg[make_pair(d, c)] = omg[make_pair(d - 1, c - 1)];
                    }
                    else //use
                    {
                        dp[d][c] = dp[d - 1][c + 1];
                        p[d][c] = p[d - 1][c + 1];
                        vector<int> tmp = omg[make_pair(d - 1, c + 1)];
                        tmp.push_back(d);
                        omg[make_pair(d, c)] = tmp;
                    }
                }
                else //use
                {
                    dp[d][c] = dp[d - 1][c + 1];
                    p[d][c] = p[d - 1][c + 1];
                    vector<int> tmp = omg[make_pair(d - 1, c + 1)];
                    tmp.push_back(d);
                    omg[make_pair(d, c)] = tmp;
                }
            }
            else
            {
                if (dp[d - 1][c] + arr[d] < dp[d - 1][c + 1])
                {
                    dp[d][c] = dp[d - 1][c] + arr[d];
                    p[d][c] = p[d - 1][c];
                    omg[make_pair(d, c)] = omg[make_pair(d - 1, c)];
                }
                else //use
                {
                    dp[d][c] = dp[d - 1][c + 1];
                    p[d][c] = p[d - 1][c + 1];
                    vector<int> tmp = omg[make_pair(d - 1, c + 1)];
                    tmp.push_back(d);
                    omg[make_pair(d, c)] = tmp;
                }
            }
        }
    }
     
    for (int i = 0; i < n; i++)
    {
        ans = min(dp[n][i], ans);
    }
    for (int i = 0; i < n; i++)
    {
        if (dp[n][i] == ans)
        {
            k1 = max(k1, i);
        }
    }
    cout << ans << endl;
    cout << k1 << ' ' << p[n][k1] - k1 << endl;
    vector<int> rly = omg[make_pair(n, k1)];
    for (int i = 0; i < rly.size(); i++)
    {
        cout << rly[i] << endl;
    }
    return 0;
}