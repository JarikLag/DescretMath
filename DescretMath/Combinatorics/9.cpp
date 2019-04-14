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
 
void generateCombineObject(int count, int open, int close, string ans)
{
    if (count * 2 == open + close)
    {
        cout << ans << endl;
        return;
    }
    if (open < count)
    {
        ans += '(';
        generateCombineObject(count, open + 1, close, ans);
        ans.pop_back();
    }
    if (close < open)
    {
        ans += ')';
        generateCombineObject(count, open, close + 1, ans);
        ans.pop_back();
    }
}
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);
    int n;
    cin >> n;
    generateCombineObject(n, 0, 0, "");
    return 0;
}