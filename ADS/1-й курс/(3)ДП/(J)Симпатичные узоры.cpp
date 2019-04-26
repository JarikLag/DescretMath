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
    return s;
}
 
bool check(string a, string b)
{
    for (int i = 0; i < a.size() - 1; i++)
    {
        if (a[i] == a[i + 1] && a[i + 1] == b[i] && b[i] == b[i + 1])
            return false;
    }
    return true;
}
 
int dp[1 << 10][1 << 10];
LL ans[30][1 << 10];
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("nice.in", "r", stdin);
    freopen("nice.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    if (n > m)
        swap(n, m);
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < (1 << n); j++)
        {
            if (check(toBinaryString(i, n), toBinaryString(j, n)))
            {
                dp[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < (1 << n); i++)
        ans[0][i] = 1;
    for (int k = 1; k < m; k++)
    {
        for (int i = 0; i < (1 << n); i++)
        {
            for (int j = 0; j < (1 << n); j++)
            {
                ans[k][i] += ans[k - 1][j] * dp[j][i];
            }
        }
    }
    LL sum = 0;
    for (int i = 0; i < (1 << n); i++)
    {
        sum += ans[m - 1][i];
    }
    cout << sum;
    return 0;
}