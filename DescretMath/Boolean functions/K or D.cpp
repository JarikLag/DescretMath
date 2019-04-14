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
    unsigned int rez = 0;
    for (unsigned int i = 0; i < (unsigned int)s.length(); i++)
    {
        rez += (s[i] - '0') * (1 << i);
    }
    return rez;
}
 
string toString(unsigned int x)
{
    string s;
    while (x != 0)
    {
        s += ((x % 2) + '0');
        x = x >> 1;
    }
    return s;
}
 
void normalize(string &s, int size)
{
    while (s.length() != size)
    {
        s += "0";
    }
}
 
string not(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '0')
            s[i] = '1';
        else
            s[i] = '0';
    }
    return s;
}
 
int main()
{
    int n;
    unsigned int s;
    cin >> n;
    vector<unsigned int> variables(n);
    vector<string> bits(n + 1), answer;
    int maxSize = -1;
    for (int i = 0; i < n; i++)
    {
        cin >> variables[i];
        bits[i] = toString(variables[i]);
        maxSize = max(maxSize, (int)bits[i].length());
    }
    cin >> s;
    if (s == 0)
    {
        cout << "1&~1";
        return 0;
    }
    bits[n] = toString(s);
    if (bits[n].length() > maxSize)
    {
        cout << "Impossible";
        return 0;
    }
    for (int i = 0; i <= n; i++)
    {
        normalize(bits[i], 32);
    }
    for (int i = 0; i < bits[n].length(); i++)
    {
        if (bits[n][i] == '1')
        {
            string now = "", addToAns = "";
            for (int j = 0; j < n; j++)
            {
                string temp = "";
                if (bits[j][i] == '0')
                {
                    temp = not(bits[j]);
                    if (addToAns == "")
                    {
                        addToAns += "~";
                        addToAns += ((j + 1) + '0');
                    }
                    else
                    {
                        addToAns += "&~";
                        addToAns += ((j + 1) + '0');
                    }
                }
                else
                {
                    temp = bits[j];
                    if (addToAns == "")
                        addToAns += ((j + 1) + '0');
                    else
                    {
                        addToAns += "&";
                        addToAns += ((j + 1) + '0');
                    }
                }
                if (now == "")
                {
                    now = temp;
                }
                else
                {
                    for (int k = 0; k < 32; k++)
                    {
                        now[k] = (temp[k] == '1' && now[k] == '1' ? '1' : '0');
                    }
                }
            }
            for (int j = 0; j < bits[n].length(); j++)
            {
                if (now[j] == '1' && bits[n][j] == '0')
                {
                    cout << "Impossible";
                    return 0;
                }
            }
            answer.push_back(addToAns);
        }
    }
    for (int i = 0; i < answer.size(); i++)
    {
        cout << answer[i];
        if (i != answer.size() - 1)
            cout << "|";
    }
    return 0;
}