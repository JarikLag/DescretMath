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
    freopen("stack-min.in", "r", stdin);
    freopen("stack-min.out", "w", stdout);
    stack<pair<int, int> > myStack;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int type, x;
        scanf("%d", &type);
        if (type == 1)
        {
            scanf("%d", &x);
            if (myStack.empty())
                myStack.push(make_pair(x, x));
            else
            {
                myStack.push(make_pair(x, min(myStack.top().second, x)));
            }
        }
        if (type == 2)
        {
            myStack.pop();
        }
        if (type == 3)
        {
            printf("%d\n", myStack.top().second);
        }
    }
    return 0;
}