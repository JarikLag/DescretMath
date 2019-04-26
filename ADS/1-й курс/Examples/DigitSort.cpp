// CF.cpp: определяет точку входа для консольного приложения.
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
	//freopen("radixsort.in", "r", stdin);
	//freopen("radixsort.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	vector<string> arr(n), copyArr(n);
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	for (int i = m - 1; i >= 0; i--)
	{
		vector<int> radixArr(600, 0); //size of alphabet
		for (int j = 0; j < n; j++)
		{
			radixArr[(arr[j][i] - '0')]++;
		}
		int count = 0, temp = 0;
		for (int j = 0; j < 600; j++)
		{
			temp = radixArr[j];
			radixArr[j] = count;
			count += temp;
		}
		for (int j = 0; j < n; j++)
		{
			int cur = arr[j][i] - '0';
			copyArr[radixArr[cur]] = arr[j];
			radixArr[cur]++;
		}
		arr = copyArr;
	}
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << endl;
	}
	return 0;
}