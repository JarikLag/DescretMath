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
    freopen("gray.in", "r", stdin);
    freopen("gray.out", "w", stdout);
    int n;
    cin >> n;
    vector<string> arr(1 << n);
    arr[0] = "0",
    arr[1] = "1";
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < (1 << i); j++)
        {
            arr[(1 << (i + 1)) - j - 1] = "1" + arr[j];
            arr[j] = "0" + arr[j];
        }
    }
    for (int i = 0; i < (1 << n); i++)
    {
        cout << arr[i] << endl;
    }
    return 0;
}