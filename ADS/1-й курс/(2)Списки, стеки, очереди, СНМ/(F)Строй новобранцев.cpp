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
 
struct soldier
{
    int left = 0;
    int right = 0;
 
    soldier()
    {}
};
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("formation.in", "r", stdin);
    freopen("formation.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<soldier> arr(n + 2);
    for (int k = 0; k < m; k++)
    {
        string s;
        int i, j;
        cin >> s;
        if (s == "left")
        {
            cin >> i >> j;
            arr[arr[j].left].right = i;
            arr[i].left = arr[j].left;
            arr[i].right = j;
            arr[j].left = i;
        }
        else if (s == "right")
        {
            cin >> i >> j;
            arr[arr[j].right].left = i;
            arr[i].left = j;
            arr[i].right = arr[j].right;
            arr[j].right = i;
        }
        else if (s == "leave")
        {
            cin >> i;
            arr[arr[i].left].right = arr[i].right;
            arr[arr[i].right].left = arr[i].left;
        }
        else
        {
            cin >> i;
            cout << arr[i].left << ' ' << arr[i].right << endl;
        }
    }
    return 0;
}