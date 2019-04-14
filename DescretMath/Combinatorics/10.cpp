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
 
void generateCombineObject(int value, int now, vector<int> ans)
{
    if (value == 0)
    {
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i];
            if (i != ans.size() - 1)
                cout << '+';
        }
        cout << endl;
        return;
    }
    for (int i = now; i <= value; i++)
    {
        ans.push_back(i);
        generateCombineObject(value - i, i, ans);
        ans.pop_back();
    }
}
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> ans;
    generateCombineObject(n, 1, ans);
    return 0;
}