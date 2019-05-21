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
 
int toInt(string s)
{
    int p = 0, ans = 0;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        ans += (s[i] - '0') * pow(10, p);
        p++;
    }
    return ans;
}
 
int dp[1001][1001];
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string a, b;
    cin >> a >> b;
    for (int i = 0; i <= a.length(); i++)
    {
        for (int j = 0; j <= b.length(); j++)
        {
            if (i == 0 && j == 0)
            {
                dp[i][j] = 0;
            }
            else if (i == 0 && j > 0)
            {
                dp[i][j] = j;
            } 
            else if (i > 0 && j == 0)
            {
                dp[i][j] = i;
            }
            else
            {
                dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? 0 : 1));
            }
        }
    }
    cout << dp[a.length()][b.length()];
    return 0;
}