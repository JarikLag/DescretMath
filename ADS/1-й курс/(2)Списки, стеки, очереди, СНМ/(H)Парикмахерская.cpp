 
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
 
struct Node
{
    int minute;
    int ind;
 
    Node()
    {}
 
    Node(int m, int p)
    {
        minute = m;
        ind = p;
    }
};
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("saloon.in", "r", stdin);
    freopen("saloon.out", "w", stdout);
    queue<Node> q;
    int n;
    cin >> n;
    vector<int> times(n);
    for (int i = 0; i < n; i++)
    {
        int h, m, p;
        cin >> h >> m >> p;
        if (q.empty())
        {
            q.push(Node(h * 60 + m, i));
        }
        else
        {
            while (!q.empty())
            {
                Node now = q.front();
                int t1 = (now.minute + 20) % 1440, t2 = 60 * h + m;
                if (t1 <= t2)
                {
                    q.pop();
                    times[now.ind] = t1;
                }
                else
                {
                    break;
                }
            }
            if (q.size() <= p)
            {
                if (q.size() == 0)
                    q.push(Node(60 * h + m, i));
                else
                    q.push(Node((q.back().minute + 20) % 1440, i));
            }
            else
            {
                times[i] = (h * 60 + m);
            }
        }
    }
    int first, sz;
    if (q.size() >= 1)
    {
        first = (q.front().minute + 20) % 1440;
        times[q.front().ind] = first;
        q.pop();
    }
    sz = q.size();
    for (int i = 0; i < sz; i++)
    {
        first += 20;
        times[q.front().ind] = (first % 1440);
        q.pop();
    }
    for (int i = 0; i < n; i++)
    {
        cout << times[i] / 60 << ' ' << times[i] % 60 << endl;
    }
    return 0;
}