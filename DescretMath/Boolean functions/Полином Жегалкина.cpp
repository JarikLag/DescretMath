// CF.cpp: ?????????? ????? ????? ??? ??????????? ??????????.
//
 
#include <cstdio>
#include <iostream>
#include <vector>
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
    //freopen("trains.in", "r", stdin);
    //freopen("trains.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> arr(1025), ans(1025);
    vector<string> strs(1025);
    for (int i = 0; i < (1 << n); i++)
    {
        cin >> strs[i] >> arr[i];
    }
    ans[0] = arr[0];
    int cnt = 1;
    for (int i = 1; i < 1 << n; i++)
    {
        for (int j = 0; j < (1 << n) - cnt; j++)
        {
            arr[j] = (arr[j] ^ arr[j + 1]);
        }
        ans[i] = arr[0];
        cnt++;
    }
    for (int i = 0; i < (1 << n); i++)
    {
        cout << strs[i] << ' ' << ans[i] << endl;
    }
    return 0;
}