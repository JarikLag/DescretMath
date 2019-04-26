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
 
int dp[101][101], p[101][101];
 
int main()
{
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    string s;
    cin >> s;
    int len = s.length();
    for (int i = 0; i < 101; i++)
    {
        for (int j = 0; j < 101; j++)
            if (i == j)
                dp[i][i] = 1;
            else if (i > j)
                dp[i][j] = 0;
            else
                dp[i][j] = 1e9;     
    }
    for (int r = 0; r < len; r++)
    {
        for (int l = r; l >= 0; l--)
        {
            int nowp = -1;
            if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']') || (s[l] == '{' && s[r] == '}'))
            {
                dp[l][r] = min(dp[l + 1][r - 1], dp[l][r]);
            }
            for (int k = l; k < r; k++)
            {
                if (dp[l][r] > dp[l][k] + dp[k + 1][r])
                {
                    dp[l][r] = dp[l][k] + dp[k + 1][r];
                    nowp = k;
                }
            }
            p[l][r] = nowp;
        }
    }
    cout << len - dp[0][len - 1];
    return 0;
}