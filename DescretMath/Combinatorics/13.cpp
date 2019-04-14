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
 
vector<int> toFactoradic(LL x, int size)
{
    vector<int> s;
    int i = 1;
    while (x != 0)
    {
        s.push_back(x % i);
        x /= i;
        i++;
    }
    while (s.size() != size)
    {
        s.push_back(0);
    }
    reverse(s.begin(), s.end());
    return s;
}
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("num2perm.in", "r", stdin);
    freopen("num2perm.out", "w", stdout);
    LL n, k, fact = 1;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = (i + 1);
    }
    vector<int> s = toFactoradic(k, n);
    for (int i = 0; i < n; i++)
    {
        cout << arr[s[i]] << ' ';
        arr.erase(arr.begin() + s[i]);
    }
    return 0;
}