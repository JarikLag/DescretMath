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
 
int dp[101][10];
int p[10][3] = { {4, 6, -1},    //0
                    {8, 6, -1}, //1
                    {7, 9, -1}, //2
                    {8, 4, -1}, //3
                    {3, 9, 0},  //4
                    {-1, -1, -1},//5
                    {1, 7, 0},   //6
                    {6, 2, -1},  //7
                    {1, 3, -1},  //8
                    {4, 2, -1} }; //9
 
int main()
{
    ios::sync_with_stdio(false);
    //freopen("num2brackets2.in", "r", stdin);
    //freopen("num2brackets2.out", "w", stdout);
    int n, mod = 1e9;
    cin >> n;
    if (n == 1)
    {
        cout << 8;
        return 0;
    }
    for (int i = 0; i < 10; i++)
        dp[1][i] = 1;
    for (int i = 2; i <= 100; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (p[j][k] != -1)
                    dp[i][j] = (dp[i][j] + dp[i - 1][p[j][k]]) % mod;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 10; i++)
    {
        if (i != 0 && i != 8)
        {
            ans = (ans + dp[n][i]) % mod;
        }
    }
    cout << ans;
    return 0;
}