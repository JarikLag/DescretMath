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
    return s;
}
 
string toTernaryString(int x, int size)
{
    string s;
    while (x != 0)
    {
        s += ((x % 3) + '0');
        x /= 3;
    }
    while (s.length() != size)
    {
        s += '0';
    }
    reverse(s.begin(), s.end());
    return s;
}
 
bool compareStrings(string a, string b)
{
    for (int i = 0; i < a.length(); i++)
    {
        if (b[i] < a[i])
            return false;
    }
    return true;
}
 
int main()
{
    ios::sync_with_stdio(false);
    freopen("chaincode.in", "r", stdin);
    freopen("chaincode.out", "w", stdout);
    int n;
    cin >> n;
    vector<string> arr(1 << n);
    set<string> mySet;
    arr[0] = toBinaryString(0, n);
    mySet.insert(arr[0]);
    for (int j = 1; j < (1 << n); j++)
    {
        if (mySet.find(arr[j - 1].substr(1, n - 1) + "1") == mySet.end())
        {
            mySet.insert(arr[j - 1].substr(1, n - 1) + "1");
            arr[j] = arr[j - 1].substr(1, n - 1) + "1";
        } 
        else if (mySet.find(arr[j - 1].substr(1, n - 1) + "0") == mySet.end())
        {
            mySet.insert(arr[j - 1].substr(1, n - 1) + "0");
            arr[j] = arr[j - 1].substr(1, n - 1) + "0";
        }
    }
    for (int i = 0; i < (1 << n); i++)
    {
        cout << arr[i] << endl;
    }
    return 0;
}