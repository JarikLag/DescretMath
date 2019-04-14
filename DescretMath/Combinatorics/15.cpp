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
 
LL C[31][31]; //C[n][k]
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("num2choose.in", "r", stdin);
    freopen("num2choose.out", "w", stdout);
    LL n, k, m;
    cin >> n >> k >> m;
    for (int i = 0; i <= 30; i++)
    {
        C[i][0] = 1;
        C[i][i] = 1;
        for (int j = 1; j < i; j++)
        {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    LL now_n = n - 1, now_k = k - 1, now_m = -1;
    vector<int> ans;
    for (int i = 1; i <= n; i++)
    {
        if (now_m == m || ans.size() == k)
        {
            while (ans.size() != k)
            {
                ans.push_back(i);
                i++;
            }
            break;
        }
        if (now_m + C[now_n][now_k] < m)
        {
            now_m += C[now_n][now_k];
            now_n--;
            continue;
        }
        if (now_m + C[now_n][now_k] > m)
        {
            now_n--;
            now_k--;
            ans.push_back(i);
            continue;
        }
        if (now_m + C[now_n][now_k] == m)
        {
            now_n--;
            now_k--;
            ans.push_back(i);
            continue;
        }
    }
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}