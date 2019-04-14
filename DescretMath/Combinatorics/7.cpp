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
 
string toFactoradic(int x, int size)
{
    string s;
    int i = 1;
    while (x != 0)
    {
        s += ((x % i) + '0');
        x /= i;
        i++;
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
    freopen("permutations.in", "r", stdin);
    freopen("permutations.out", "w", stdout);
    int n, fact = 1;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
        fact *= (i + 1);
    }
    for (int i = 0; i < fact; i++)
    {
        vector<int> tmp = arr;
        string s = toFactoradic(i, n);
        for (int j = 0; j < n; j++)
        {
            cout << tmp[s[j] - '0'] << " ";
            tmp.erase(tmp.begin() + (s[j] - '0'));
        }
        cout << endl;
    }
    return 0;
}