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
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("hemoglobin.in", "r", stdin);
    freopen("hemoglobin.out", "w", stdout);
    int n, size = 0;
    cin >> n;
    vector<LL> a(n + 1), pref(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        char c;
        LL x;
        cin >> c;
        if (c == '+')
        {
            cin >> x;
            a[size] = x;
            size++;
            pref[size] = pref[size - 1] + x;
        }
        else if (c == '-')
        {
            size--;
            cout << a[size] << endl;
        }
        else
        {
            cin >> x;
            cout << pref[size] - pref[size - x] << endl;
        }
    }
    return 0;
}