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
    freopen("nextmultiperm.in", "r", stdin);
    freopen("nextmultiperm.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int ind = -1;
    for (int i = n - 2; i >= 0; i--)
    {
        if (arr[i] < arr[i + 1])
        {
            ind = i;
            break;
        }
    }
    if (ind == -1)
    {
        for (int i = 0; i < n; i++)
        {
            cout << "0 ";
        }
        return 0;
    }
    else
    {
        int min = 1e9, minInd = -1;
        for (int i = ind + 1; i < n; i++)
        {
            if (arr[i] > arr[ind] && min > arr[i])
            {
                minInd = i;
                min = arr[i];
            }
        }
        swap(arr[ind], arr[minInd]);
        vector<int> tmp;
        for (int i = n - 1; i > ind; i--)
        {
            tmp.push_back(arr[i]);
        }
        sort(tmp.begin(), tmp.end());
        for (int i = 0; i <= ind; i++)
        {
            cout << arr[i] << ' ';
        }
        for (int i = 0; i < tmp.size(); i++)
        {
            cout << tmp[i] << ' ';
        }
    }
    return 0;
}