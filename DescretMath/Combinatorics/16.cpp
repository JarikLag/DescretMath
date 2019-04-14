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
    freopen("choose2num.in", "r", stdin);
    freopen("choose2num.out", "w", stdout);
    LL n, k;
    cin >> n >> k;
    vector<int> arr(k);
    for (int i = 0; i < k; i++)
    {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    for (int i = 0; i <= 30; i++)
    {
        C[i][0] = 1;
        C[i][i] = 1;
        for (int j = 1; j < i; j++)
        {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    LL now_n = n - 1, now_k = k - 1, ind = 0, size = 0, number = 0;
    for (int i = 1; i <= n; i++)
    {
        if (size == k)
        {
            break;
        }
        if (arr[ind] == i)
        {
            now_k--;
            now_n--;
            ind++;
            size++;
            continue;
        }
        number += C[now_n][now_k];
        now_n--;
    }
    cout << number;
    return 0;
}