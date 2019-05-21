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
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<int> arr(n, 0), dp(n + 1, 0), p(n + 1, -1), ans;
    for (int i = 1; i < n - 1; i++)
    {
        cin >> arr[i];
    }
    for (int i = 1; i < n; i++)
    {
        int maxInd = -1, nowInd = max(0, i - k), maxVal = -1e9;
        for (int j = nowInd; j < i; j++)
        {
            if (maxVal < dp[j])
            {
                maxVal = dp[j];
                maxInd = j;
            }
        }
        dp[i] = dp[maxInd] + arr[i];
        p[i] = maxInd;
    }
    cout << dp[n - 1] << endl;
    int ind = n - 1;
    while (ind != -1)
    {
        ans.push_back(ind + 1);
        ind = p[ind];
    }
    cout << ans.size() - 1 << endl;
    for (int i = ans.size() - 1; i >= 0; i--)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}