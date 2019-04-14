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
 
LL dp[102][102];
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("num2part.in", "r", stdin);
    freopen("num2part.out", "w", stdout);
    for (int i = 0; i < 102; i++)
        dp[i][i] = 1;
    for (int i = 1; i < 101; i++)
        for (int j = i - 1; j >= 0; j--)
            dp[i][j] = dp[i][j + 1] + dp[i - j][j];
    LL n, k, num = 0, sum = 0, ncopy;
    cin >> n >> k;
    ncopy = n;
    vector<int> ans;
    for (int i = 1; i <= n; i++)
    {
        if (sum + i == n)
        {
            ans.push_back(i);
            break;
        }
        if (num + dp[ncopy - i][i] - 1 >= k)
        {
            ans.push_back(i);
            sum += i;
            ncopy -= i;
            i--;
        }
        else
        {
            num += dp[ncopy - i][i];
        }
    }
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i];
        if (i != ans.size() - 1)
            cout << '+';
    }
    return 0;
}