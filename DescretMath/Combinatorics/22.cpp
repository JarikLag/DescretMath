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
 
LL dp[102][102];
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("part2num.in", "r", stdin);
    freopen("part2num.out", "w", stdout);
    for (int i = 0; i < 102; i++)
        dp[i][i] = 1;
    for (int i = 1; i < 101; i++)
        for (int j = i - 1; j >= 0; j--)
            dp[i][j] = dp[i][j + 1] + dp[i - j][j];
    LL k = 0, n = 0;
    int pos = 0;
    string s;
    cin >> s;
    vector<int> arr;
    for (int i = 0; i < s.length(); i++)
    {
        if (i == s.length() - 1)
        {
            arr.push_back(toInt(s.substr(pos, i - pos + 1)));
            n += arr.back();
        }
        if (s[i] == '+')
        {
            arr.push_back(toInt(s.substr(pos, i - pos)));
            pos = i + 1;
            n += arr.back();
        }
    }
    int now = 1;
    for (int i = 0; i < arr.size(); i++)
    {
        while (arr[i] != now)
        {
            k += dp[n - now][now];
            now++;
        }
        n -= now;
    }
    cout << k;
    return 0;
}