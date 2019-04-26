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
    freopen("decode.in", "r", stdin);
    freopen("decode.out", "w", stdout);
    stack<char> myStack;
    string s, ans;
    cin >> s;
    for (int i = 0; i < s.length(); i++)
    {
        if (myStack.empty())
        {
            myStack.push(s[i]);
        }
        else
        {
            if (myStack.top() == s[i])
                myStack.pop();
            else
                myStack.push(s[i]);
        }
    }
    while (!myStack.empty())
    {
        ans += myStack.top();
        myStack.pop();
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
    return 0;
}