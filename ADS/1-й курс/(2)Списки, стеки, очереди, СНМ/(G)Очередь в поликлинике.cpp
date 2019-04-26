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
    ios::sync_with_stdio(false);
    freopen("hospital.in", "r", stdin);
    freopen("hospital.out", "w", stdout);
    int n;
    vector<int> arr;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char c;
        int x;
        cin >> c;
        if (c == '+')
        {
            cin >> x;
            arr.push_back(x);
        }
        else if (c == '*')
        {
            cin >> x;
            vector<int>::iterator pos = arr.begin() + (arr.size() % 2 == 0 ? arr.size() / 2 : arr.size() / 2 + 1);
            arr.insert(pos, x);
        }
        else
        {
            cout << arr[0] << endl;
            arr.erase(arr.begin());
        }
    }
    return 0;
}