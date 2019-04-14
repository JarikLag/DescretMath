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
    int n, k;
    cin >> n >> k;
    vector<vector<int> > brackets(k, vector<int>(n));
    vector<int> variables(n, -1);
    vector<int> sizeOfBrackets(k, 0);
    vector<bool> exist(k, true);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> brackets[i][j];
            if (brackets[i][j] != -1)
                sizeOfBrackets[i]++;
        }
    }
    while (true)
    {
        int singleBracketIndex = -1, variableIndex;
        for (int i = 0; i < k; i++)
        {
            if (sizeOfBrackets[i] == 1 && exist[i])
            {
                for (int j = 0; j < n; j++)
                {
                    if (brackets[i][j] != -1)
                    {
                        variableIndex = j;
                        break;
                    }
                }
                sizeOfBrackets[i]--;
                exist[i] = false;
                singleBracketIndex = i;
                break;
            }
        }
 
        if (singleBracketIndex == -1)
        {
            cout << "NO";
            break;
        }
 
        if (brackets[singleBracketIndex][variableIndex] == 0)
        {
            variables[variableIndex] = 0;
        }
        else
        {
            variables[variableIndex] = 1;
        }
 
        for (int i = 0; i < k; i++)
        {
            if (exist[i])
            {
                if (brackets[i][variableIndex] != -1)
                {
                    if ((brackets[i][variableIndex] == 0 && variables[variableIndex] == 1) 
                        || (brackets[i][variableIndex] == 1 && variables[variableIndex] == 0))
                    {
                        brackets[i][variableIndex] = -1;
                        sizeOfBrackets[i]--;
                    }
                    else
                    {
                        exist[i] = false;
                    }
                }
                else
                {
                    continue;
                }
            }
            if (exist[i] && sizeOfBrackets[i] == 0)
            {
                cout << "YES";
                return 0;
            }
        }
    }
    return 0;
}