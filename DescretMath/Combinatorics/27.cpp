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
    freopen("nextbrackets.in", "r", stdin);
    freopen("nextbrackets.out", "w", stdout);
    string s;
    cin >> s;
    int balance = 0, position = -1;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if (s[i] == ')')
            balance++;
        else
            balance--;
        if (s[i] == '(' && balance > 0)
        {
            position = i;
            s[i] = ')';
            break;
        }
    }
    if (position == -1)
    {
        cout << '-';
        return 0;
    }
    int open = 0;
    for (int i = 0; i <= position; i++)
    {
        if (s[i] == '(')
            open++;
        cout << s[i];
    }
    open = (s.length() / 2 - open);
    int i;
    for (i = position + 1; i < position + 1 + open; i++)
        cout << '(';
    for (;i < s.length(); i++)
        cout << ')';
    return 0;
}