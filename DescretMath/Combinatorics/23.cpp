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
 
LL factor(int x)
{
    LL ans = 1;
    if (x == 0)
        return 1;
    else
    {
        for (int i = 1; i <= x; i++)
        {
            ans *= i;
        }
        return ans;
    }
}
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("nextvector.in", "r", stdin);
    freopen("nextvector.out", "w", stdout);
    string s, prev;
    cin >> s;
    prev = s;
    bool success = false;
    for (int i = prev.length() - 1; i >= 0; i--)
    {
        if (prev[i] == '1')
        {
            prev[i] = '0';
            for (int j = i + 1; j < prev.length(); j++)
            {
                prev[j] = '1';
            }
            success = true;
            break;
        }
    }
    if (!success)
        prev = "-";
    bool bit = true;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if (s[i] == '1')
        {
            s[i] = '0';
            bit = true;
        }
        else
        {
            s[i] = '1';
            bit = false;
            break;
        }
    }
    if (bit)
    {
        s = "-";
    }
    cout << prev << endl << s;
    return 0;
}