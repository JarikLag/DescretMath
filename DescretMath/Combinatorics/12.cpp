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
 
int toInt(string s)
{
    int p = 0, ans = 0;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        ans += (s[i] - '0') * pow(10, p);
        p++;
    }
    return ans;
}
 
void generateObject(int n, int k, vector<vector<int> > &sets, set<int> used)
{
    for (int i = sets.size() - 1; i >= 0; i--)
    {
        bool complete = false;
        int size = sets[i].size();
        for (int j = sets[i].size() - 1; j >= 0; j--)
        {
            if (used.size() == 0)
            {
                used.insert(sets[i][j]);
                sets[i].pop_back();
            }
            else if (j == size - 1)
            {
                auto elem = used.end();
                elem--;
                if (sets[i][j] < *elem)
                {
                    auto now = used.begin();
                    while (sets[i][j] > *now)
                        now++;
                    elem = now;
                    sets[i].push_back(*elem);
                    used.erase(*elem);
                    while (used.size())
                    {
                        vector<int> tmp;
                        tmp.push_back(*used.begin());
                        sets.push_back(tmp);
                        used.erase(*used.begin());
                    }
                    complete = true;
                    break;
                }
                else
                {
                    used.insert(sets[i][j]);
                    sets[i].pop_back();
                }
            }
            else if(j == 0)
            {
                used.insert(sets[i][j]);
                sets[i].pop_back();
            } 
            else
            {
                auto now = used.begin();
                while (sets[i][j] > *now)
                    now++;
                int elem = *now;
                used.insert(sets[i][j]);
                sets[i][j] = elem;
                used.erase(elem);
                while (used.size())
                {
                    vector<int> tmp;
                    tmp.push_back(*used.begin());
                    sets.push_back(tmp);
                    used.erase(*used.begin());
                }
                complete = true;
                break;
            }
        }
        if (sets[i].size() == 0)
            sets.pop_back();
        if (complete)
            break;
    }
}
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("part2sets.in", "r", stdin);
    freopen("part2sets.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<vector<int> > sets;
    for (int i = 1; i <= n; i++)
    {
        vector<int> tmp;
        tmp.push_back(i);
        sets.push_back(tmp);
    }
    while (sets.size())
    {
        if (sets.size() == k)
        {
            for (int i = 0; i < sets.size(); i++)
            {
                for (int j = 0; j < sets[i].size(); j++)
                {
                    cout << sets[i][j] << ' ';
                }
                cout << endl;
            }
            cout << endl;
        }       
        set<int> used;
        generateObject(n, k, sets, used);
    }   
    return 0;
}