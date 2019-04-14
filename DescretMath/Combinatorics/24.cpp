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
 
int toIntFromBinary(string s)
{
    int rez = 0;
    for (int i = 0; i < s.length(); i++)
    {
        rez += (s[i] - '0') * (1 << i);
    }
    return rez;
}
 
string toBinaryString(int x, int size)
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
    reverse(s.begin(), s.end());
    return s;
}
 
string toRandomString(int x, int size, int sys)
{
    string s;
    while (x != 0)
    {
        s += ((x % sys) + '0');
        x /= sys;
    }
    while (s.length() != size)
    {
        s += '0';
    }
    reverse(s.begin(), s.end());
    return s;
}
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("nextperm.in", "r", stdin);
    freopen("nextperm.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> arr(n + 1), next(n + 1), prev(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    next = arr;
    bool hasNext = false;
    set<int> nextSet;
    for (int i = n - 1; i >= 0; i--)
    {
        nextSet.insert(next[i]);
        auto it = nextSet.end();
        it--;
        if (next[i] < *it)
        {
            it = nextSet.begin();
            while (next[i] >= *it)
                it++;
            next[i] = *it;
            nextSet.erase(next[i]);
            for (int j = i + 1; j < n; j++)
            {
                next[j] = *nextSet.begin();
                nextSet.erase(next[j]);
            }
            hasNext = true;
            break;
        }
    }
    prev = arr;
    bool hasPrev = false;
    set<int> prevSet;
    for (int i = n - 1; i >= 0; i--)
    {
        prevSet.insert(prev[i]);
        auto it = prevSet.begin();
        if (prev[i] > *it)
        {
            while (prev[i] > *it)
                it++;
            it--;
            prev[i] = *it;
            prevSet.erase(prev[i]);
            for (int j = i + 1; j < n; j++)
            {
                auto itt = prevSet.end();
                itt--;
                prev[j] = *(itt);
                prevSet.erase(prev[j]);
            }
            hasPrev = true;
            break;
        }
    }
    if (!hasPrev)
    {
        for (int i = 0; i < n; i++)
        {
            cout << 0 << ' ';
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            cout << prev[i] << ' ';
        }
    }
    cout << endl;
    if (!hasNext)
    {
        for (int i = 0; i < n; i++)
        {
            cout << 0 << ' ';
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            cout << next[i] << ' ';
        }
    }
    return 0;
}