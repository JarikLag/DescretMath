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

void qSort(vector<int> &a, int l, int r)
{
	srand(0);
	int v = a[rand() % (r - l + 1) + l];
	int i = l, j = r;
	while (i <= j)
	{
		while (a[i] < v)
			i++;
		while (a[j] > v)
			j--;
		if (i <= j)
		{
			swap(a[i], a[j]);
			j--;
			i++;
		}
	}
	if (l < j)
		qSort(a, l, j);
	if (i < r)
		qSort(a, i, r);
}

int main() 
{
	//freopen("sort.in", "r", stdin);
	//freopen("sort.out", "w", stdout);
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	qSort(arr, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		cout << arr[i];
		if (i != n - 1)
			cout << ' ';
	}
	return 0;
}