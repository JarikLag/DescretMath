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
    freopen("postfix.in", "r", stdin);
    freopen("postfix.out", "w", stdout);
    stack<int> myStack;
    string s;
    while (cin >> s)
    {
        if (isdigit(s[0]) || (s.length() > 1))
        {
            int x = 0, tpow = 1;
            if (s[0] == '-')
            {
                for (int i = s.length() - 1; i > 0; i--)
                {
                    x += (s[i] - '0') * tpow;
                    tpow *= 10;
                }
                x *= -1;
            }
            else
            {
                for (int i = s.length() - 1; i >= 0; i--)
                {
                    x += (s[i] - '0') * tpow;
                    tpow *= 10;
                }
            }
            myStack.push(x);
        }
        else
        {
            int a, b;
            a = myStack.top();
            myStack.pop();
            b = myStack.top();
            myStack.pop();
            if (s[0] == '+')
                myStack.push(a + b);
            if (s[0] == '-')
                myStack.push(b - a);
            if (s[0] == '*')
                myStack.push(a * b);
        }
    }
    cout << myStack.top();
    return 0;
}