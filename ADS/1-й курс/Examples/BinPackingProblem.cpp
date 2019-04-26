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
 
pair<int, int> dp[1 << 18];
int arr[19];
vector<vector<vector<int> > > lift((1 << 18), vector<vector<int> >());
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("skyscraper.in", "r", stdin);
    freopen("skyscraper.out", "w", stdout);
    int n, s;
    cin >> n >> s;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 0; i < (1 << n); i++)
    {
        dp[i] = make_pair(INF, INF);
    }
    dp[0] = make_pair(0, INF);
    for (int mask = 0; mask < (1 << n); mask++)
    {
        for (int x = 0; x < n; x++)
        {
            if ((mask & (1 << x)) == 0)
            {
                if (dp[mask].second + arr[x] <= s)
                {
                    if (dp[mask | (1 << x)] > make_pair(dp[mask].first, dp[mask].second + arr[x]))
                    {
                        dp[mask | (1 << x)] = make_pair(dp[mask].first, dp[mask].second + arr[x]);
                        lift[mask | (1 << x)] = lift[mask];
                        lift[mask | (1 << x)].back().push_back(x);
                    }
                }
                else
                {
                    if (dp[mask | (1 << x)] > make_pair(dp[mask].first + 1, arr[x]))
                    {
                        dp[mask | (1 << x)] = make_pair(dp[mask].first + 1, arr[x]);
                        vector<int> tmp;
                        tmp.push_back(x);
                        lift[mask | (1 << x)] = lift[mask];
                        lift[mask | (1 << x)].push_back(tmp);
                    }
                }
            }
        }
    }
    cout << dp[(1 << n) - 1].first << endl;
    for (int i = 0; i < lift[(1 << n) - 1].size(); i++)
    {
        cout << lift[(1 << n) - 1][i].size() << ' ';
        for (int j = 0; j < lift[(1 << n) - 1][i].size(); j++)
        {
            cout << lift[(1 << n) - 1][i][j] + 1 << ' ';
        }
        cout << endl;
    }
    return 0;
}