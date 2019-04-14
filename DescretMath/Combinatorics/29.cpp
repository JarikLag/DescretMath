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
 
int toInt(string s)
{
    int p = 0, ans = 0;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        ans += (s[i] - '0') * pow(10, p);
        p++;
    }
    return ans;
}
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("nextpartition.in", "r", stdin);
    freopen("nextpartition.out", "w", stdout);
    int n;
    scanf("%d=", &n);
    string s;
    cin >> s;
    int pos = 0;
    vector<int> arr;
    for (int i = 0; i < s.length(); i++)
    {
        if (i == s.length() - 1)
        {
            arr.push_back(toInt(s.substr(pos, i - pos + 1)));
        }
        if (s[i] == '+')
        {
            arr.push_back(toInt(s.substr(pos, i - pos)));
            pos = i + 1;
        }
    }
    if (arr.size() == 1)
    {
        cout << "No solution";
        return 0;
    }
    int prev = arr.size() - 2, last = arr.size() - 1;
    arr[prev]++, arr[last]--;
    if (arr[prev] > arr[last])
    {
        arr[prev] += arr[last];
        arr.pop_back();
    }
    else
    {
        while (arr[prev] * 2 <= arr[last])
        {
            int next = arr[last] - arr[prev];
            arr[last] = arr[prev];
            prev++;
            last++;
            arr.push_back(next);
        }
    }
    cout << n << '=';
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i];
        if (i != arr.size() - 1)
            cout << '+';
    }
    return 0;
}