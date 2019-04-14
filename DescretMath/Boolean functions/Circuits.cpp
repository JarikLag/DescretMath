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
 
unsigned int toInt(string s)
{
    reverse(s.begin(), s.end());
    int rez = 0;
    for (int i = 0; i < s.length(); i++)
    {
        rez += (s[i] - '0') * (1 << i);
    }
    return rez;
}
 
string toString(int x, int size)
{
    string s;
    while (x != 0)
    {
        s += ((x % 2) + '0');
        x = x >> 1;
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
    int n, numberOfVariables = 0;
    cin >> n;
    vector<vector<int> > graph(n);
    vector<string> table(n);
    vector<int> deep(n, 0);
    vector<char> typeOfElement(n);
    for (int i = 0; i < n; i++)
    {
        int m;
        cin >> m;
        if (m == 0)
        {
            numberOfVariables++;
            typeOfElement[i] = 'l';
        }
        else
        {
            typeOfElement[i] = 'c';
            for (int j = 0; j < m; j++)
            {
                int a;
                cin >> a;
                a--;
                graph[i].push_back(a);
            }
            string toTable;
            for (int j = 0; j < (1 << m); j++)
            {
                int c;
                cin >> c;
                toTable += (c + '0');
            }
            table[i] = toTable;
        }
    }
    int size = 1 << numberOfVariables;
    string ans;
    vector<char> tempValue(n);
    for (int i = 0; i < size; i++)
    {
        string now = toString(i, numberOfVariables);
        int ind = 0;
        for (int j = 0; j < n; j++)
        {
            if (typeOfElement[j] == 'l')
            {
                tempValue[j] = now[ind];
                ind++;
            }
            else
            {
                string indexString = "";
                int maxDeep = -1;
                for (int k = 0; k < graph[j].size(); k++)
                {
                    maxDeep = max(maxDeep, deep[graph[j][k]]);
                    indexString += tempValue[graph[j][k]];
                }
                tempValue[j] = table[j][toInt(indexString)];
                deep[j] = maxDeep + 1;
            }
        }
        ans += tempValue[n - 1];
    }
    cout << deep[n - 1] << endl << ans;
    return 0;
}