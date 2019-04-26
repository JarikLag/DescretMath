 
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
    freopen("bureaucracy.in", "r", stdin);
    freopen("bureaucracy.out", "w", stdout);
    LL sum = 0, m, n;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        sum += arr[i];
    }
    if (sum <= m)
    {
        cout << -1;
        return 0;
    }
    LL l = 0, r = 1e18;
    while (r - l > 1)
    {
        LL k = (l + r) / 2ll;
        LL now = 0;
        for (int i = 0; i < n; i++)
        {
            if (arr[i] < k)
                now += arr[i];
            else
                now += k;
        }
        if (now > m)
        {
            r = k;
        }
        else
        {
            l = k;
        }
    }
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] <= l)
            m -= arr[i];
        else
        {
            arr[i] -= l;
            q.push(arr[i]);
            m -= l;
        }
    }
    while (m != 0)
    {
        int now = q.front();
        q.pop();
        m--;
        if (now != 1)
            q.push(now - 1);
    }
    cout << q.size() << endl;
    while (!q.empty())
    {
        cout << q.front() << ' ';
        q.pop();
    }
    return 0;
}