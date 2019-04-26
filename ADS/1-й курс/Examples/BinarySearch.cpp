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

int arr[100001];

int lowerBinarySearch(int n, int a) //left
{
	int l = -1, r = n;
	while (l < r - 1)
	{
		int m = (l + r) / 2;
		if (arr[m] < a)
			l = m;
		else
			r = m;
	}
	if (r == n|| arr[r] != a)
		return -1;
	else
		return r + 1;
}

int upperBinarySearch(int n, int a) //right
{
	int l = -1, r = n;
	while (l < r - 1)
	{
		int m = (l + r) / 2;
		if (arr[m] <= a)
			l = m;
		else
			r = m;
	}
	if (l == -1 || arr[l] != a)
		return -1;
	else
		return l + 1;
}

int main() 
{
	freopen("binsearch.in", "r", stdin);
	freopen("binsearch.out", "w", stdout);
	int n, m;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int a;
		scanf("%d", &a);
		cout << lowerBinarySearch(n, a) << ' ' << upperBinarySearch(n, a) << endl;
	}
	return 0;
}