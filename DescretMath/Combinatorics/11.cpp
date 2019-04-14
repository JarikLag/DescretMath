 
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
 
void generateCombineObject(vector<int> arr, vector<int> buf, int ind)
{
    if (ind > arr.size())
    {
        return;
    }
    for (int i = 0; i < buf.size(); i++)
    {
        cout << buf[i] << ' ';
    }
    cout << endl;
    for (int i = ind; i < arr.size(); i++)
    {
        buf.push_back(arr[i]);
        generateCombineObject(arr, buf, i + 1);
        buf.pop_back();
    }
}
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("subsets.in", "r", stdin);
    freopen("subsets.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> arr(n), buf;
    for (int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }
    generateCombineObject(arr, buf, 0);
    return 0;
}