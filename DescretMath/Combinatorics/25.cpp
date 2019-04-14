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
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("nextchoose.in", "r", stdin);
    freopen("nextchoose.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<int> arr(k);
    for (int i = 0; i < k; i++)
    {
        cin >> arr[i];
    }
    vector<bool> used(n + 1, false);
    bool find = false;
    for (int i = k - 1; i >= 0; i--)
    {
        if (arr[i] + 1 <= n && !used[arr[i] + 1])
        {
            arr[i] += 1;
            for (int j = i + 1; j < k; j++)
            {
                arr[j] = arr[j - 1] + 1;
            }
            find = true;
            break;
        }
        else
        {
            used[arr[i]] = true;
        }
    }
    if (!find)
    {
        cout << "-1";
        return 0;
    }
    for (int i = 0; i < k; i++)
    {
        cout << arr[i] << ' ';
    }
    return 0;
}