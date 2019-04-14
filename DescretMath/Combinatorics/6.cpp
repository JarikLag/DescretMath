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
    freopen("vectors.in", "r", stdin);
    freopen("vectors.out", "w", stdout);
    int n;
    cin >> n;
    vector<string> arr;
    for (int i = 0; i < (1 << n); i++)
    {
        string s = toBinaryString(i, n);
        bool flag = true;
        for (int j = 0; j < n - 1; j++)
        {
            if (s[j] == '1' && s[j] == s[j + 1])
            {
                flag = false;
                break;
            }
        }
        if (flag)
            arr.push_back(s);
    }
    cout << arr.size() << endl;
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << endl;
    }
    return 0;
}