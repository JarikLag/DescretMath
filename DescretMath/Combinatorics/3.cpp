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
    return s;
}
 
string toTernaryString(int x, int size)
{
    string s;
    while (x != 0)
    {
        s += ((x % 3) + '0');
        x /= 3;
    }
    while (s.length() != size)
    {
        s += '0';
    }
    reverse(s.begin(), s.end());
    return s;
}
 
bool compareStrings(string a, string b)
{
    for (int i = 0; i < a.length(); i++)
    {
        if (b[i] < a[i])
            return false;
    }
    return true;
}
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("antigray.in", "r", stdin);
    freopen("antigray.out", "w", stdout);
    int n, pos = 0;
    cin >> n;
    vector<string> arr(pow(3, n));
    for (int i = 0; i < pow(3, n - 1); i++)
    {
        arr[pos] = toTernaryString(i, n);
        pos += 3;
    }
    for (int i = 0; i < pow(3, n); i += 3)
    {
        arr[i + 1] = arr[i];
        arr[i + 2] = arr[i + 1];
        for (int j = 0; j < n; j++)
        {
            arr[i + 1][j] = (((arr[i + 1][j] - '0') + 1) % 3) + '0';
            arr[i + 2][j] = (((arr[i + 1][j] - '0') + 1) % 3) + '0';
        }
    }
    for (int i = 0; i < pow(3, n); i++)
    {
        cout << arr[i] << endl;
    }
    return 0;
}