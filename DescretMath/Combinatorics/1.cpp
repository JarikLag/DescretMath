// CF.cpp: ?????????? ????? ????? ??? ??????????? ??????????.
//
 
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
 
string toString(int x, int size)
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
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("allvectors.in", "r", stdin);
    freopen("allvectors.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < (1 << n); i++)
    {
        string s = toString(i, n);
        reverse(s.begin(), s.end());
        cout << s << endl;
    }
    return 0;
}