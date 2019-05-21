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
    int min;
    int max;
    int size = 0;
 
    Node()
    {}
 
    Node(int mini, int maxi, int sizei)
    {
        min = mini;
        max = maxi;
        size = sizei;
    }
};
 
vector<int> ranking;
vector<int> parent;
vector<Node> myNode;
 
int get(int x)
{
    if (parent[x] != x)
        parent[x] = get(parent[x]);
    return parent[x];
}
 
void unite(int x, int y)
{
    x = get(x);
    y = get(y);
    if (x == y)
        return;
    if (ranking[x] == ranking[y])
        ranking[x]++;
    if (ranking[y] < ranking[x])
    {
        parent[y] = x;
        myNode[x].size += myNode[y].size;
        myNode[x].max = max(myNode[y].max, myNode[x].max);
        myNode[x].min = min(myNode[y].min, myNode[x].min);
    }
    else
    {
        parent[x] = y;
        myNode[y].size += myNode[x].size;
        myNode[y].max = max(myNode[y].max, myNode[x].max);
        myNode[y].min = min(myNode[y].min, myNode[x].min);
    }
}
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("dsu.in", "r", stdin);
    freopen("dsu.out", "w", stdout);
    int n;
    cin >> n;
    ranking.resize(n + 1, 1);
    parent.resize(n + 1, 0);
    myNode.push_back(Node());
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
        myNode.push_back(Node(i, i, 1));
    }
    string s;
    while (cin >> s)
    {
        int a, b;
        if (s == "union")
        {
            cin >> a >> b;
            unite(a, b);
        }
        else
        {
            cin >> a;
            int p = get(a);
            cout << myNode[p].min << ' ' << myNode[p].max << ' ' << myNode[p].size << endl;
        }
    }
    return 0;
}