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
 
bool open(char c)
{
    if (c == '(' || c == '[' || c == '{')
        return true;
    else
        return false;
}
 
bool sameType(char a, char b)
{
    if (a == '(' && b == ')' || a == '[' && b == ']' || a == '{' && b == '}')
        return true;
    else
        return false;
}
 
int main()
{
    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);
    stack<char> myStack;
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++)
    {
        if (myStack.empty())
        {
            if(open(s[i]))
                myStack.push(s[i]);
            else
            {
                cout << "NO";
                return 0;
            }
        }
        else
        {
            if (open(s[i]))
                myStack.push(s[i]);
            else
            {
                if (sameType(myStack.top(), s[i]))
                    myStack.pop();
                else
                {
                    cout << "NO";
                    return 0;
                }
            }
        }
    }
    if (myStack.empty())
        cout << "YES";
    else
        cout << "NO";
    return 0;
}