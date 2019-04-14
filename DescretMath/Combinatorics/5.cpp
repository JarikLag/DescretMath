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
    freopen("telemetry.in", "r", stdin);
    freopen("telemetry.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<string> arr(pow(k, n));
    for (int i = 0; i < k; i++)
    {
        arr[i] = toRandomString(i, 1, k);
    }   
    for (int i = 1; i < n; i++)
    {
        int pos = 1;
        for (int j = 0; j < pow(k, i + 1); j++)
        {
            int power = pow(k, i);
            if (j < power)
            {
                arr[j] = "0" + arr[j];
            }
            else
            {
                char ll = (j / power) + '0';
                arr[j] = arr[j - pos];
                arr[j][0] = ll;
                pos = (pos + 2) % (2 * power);
            }
        }
    }
    for (int i = 0; i < pow(k, n); i++)
    {
        cout << arr[i] << endl;
    }
    return 0;
}