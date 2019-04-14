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
 
LL fromFactoradic(vector<int> arr)
{
    LL ans = 0, ind = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        ans += (arr[i] * factor(ind));
        ind++;
    }
    return ans;
}
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("perm2num.in", "r", stdin);
    freopen("perm2num.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    vector<int> num, tmp;
    for (int i = n - 1; i >= 0; i--)
    {
        if (tmp.size() == 0)
        {
            tmp.push_back(arr[i]);
            num.push_back(0);
        }
        else
        {
            bool flag = true;
            for (int j = 0; j < tmp.size(); j++)
            {
                if (tmp[j] > arr[i])
                {
                    num.push_back(j);
                    tmp.insert(tmp.begin() + j, arr[i]);
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                num.push_back(tmp.size());
                tmp.push_back(arr[i]);
            }
        }
    }
    cout << fromFactoradic(num);
    return 0;
}