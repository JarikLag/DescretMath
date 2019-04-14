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
 
int toIntFromBinary(string s)
{
    int rez = 0;
    for (int i = 0; i < s.length(); i++)
    {
        rez += (s[i] - '0') * (1 << i);
    }
    return rez;
}
 
string toBinaryString(int x, int size)
{
    string s;
    while (x != 0)
    {
        s += ((x % 2) + '0');
        x /= 2;
    }
    while (s.length() != size)
    {
        s += '0';
    }
    reverse(s.begin(), s.end());
    return s;
}
 
string toRandomString(int x, int size, int sys)
{
    string s;
    while (x != 0)
    {
        s += ((x % sys) + '0');
        x /= sys;
    }
    while (s.length() != size)
    {
        s += '0';
    }
    reverse(s.begin(), s.end());
    return s;
}
 
LL dp[41][41];
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("brackets2num.in", "r", stdin);
    freopen("brackets2num.out", "w", stdout);
    string s;
    cin >> s;
    LL len = s.length(), ans = 0, balance = 0;
    dp[0][0] = 1;
    for (int i = 1; i <= len; i++)
    {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= len; i++)
    {
        for (int j = 0; j <= len; j++)
        {
            if (j == 0)
                dp[i][j] = dp[i - 1][j + 1];
            else if (j == len - 1)
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
        }
    }
    for (int i = 0; i < len; i++)
    {
        if (s[i] == '(')
            balance++;
        else
        {
            ans += dp[len - 1 - i][balance + 1];
            balance--;
        }
    }
    cout << ans;
    return 0;
}