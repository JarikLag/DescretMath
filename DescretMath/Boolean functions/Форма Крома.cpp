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
    int n, m;
    cin >> n >> m;
    vector<pair<int, int> > brackets;
    set<pair<int, int> > safeSet;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        if (abs(a) > abs(b))
            swap(a, b);
        safeSet.insert(make_pair(a, b));
    }
    for (auto it = safeSet.begin(); it != safeSet.end(); it++)
    {
        brackets.push_back(*it);
    }
    for (int i = 0; i < (1 << n); i++)
    {
        string now = toString(i, n);
        bool isAnyZero = false;
        for (int j = 0; j < brackets.size(); j++)
        {
            bool first = (now[abs(brackets[j].first) - 1] - '0'),
                second = (now[abs(brackets[j].second) - 1] - '0');
            if (brackets[j].first < 0)
                first = !first;
            if (brackets[j].second < 0)
                second = !second;
            if (!(second || first))
            {
                isAnyZero = true;
                break;
            }
        }
        if (!isAnyZero)
        {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}