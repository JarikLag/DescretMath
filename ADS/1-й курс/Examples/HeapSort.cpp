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
using namespace std;

typedef long long LL;

int heapSize;

void siftDown(vector<int> &a, int ind, int hSize)
{
	while (2 * ind + 1 < hSize)
	{
		int left = 2 * ind + 1;
		int right = 2 * ind + 2;
		int j = left;
		if (right < hSize && (a[right] > a[left]))
		{
			j = right;
		}
		if (a[ind] >= a[j])
		{
			break;
		}
		else
		{
			swap(a[j], a[ind]);
			ind = j;
		}
	}
}

void buildHeap(vector<int> &a)
{
	for (int i = heapSize / 2; i >= 0; i--)
	{
		siftDown(a, i, heapSize);
	}
}

void heapSort(vector<int> &a)
{
	buildHeap(a);
	heapSize = a.size();
	for (int i = 0; i < (int)a.size() - 1; i++) 
	{
		swap(a[0], a[(int)a.size() - 1 - i]);
		heapSize--;
		siftDown(a, 0, heapSize);
	}
}

int main() 
{
	//freopen("sort.in", "r", stdin);
	//freopen("sort.out", "w", stdout);
	int n;
	cin >> n;
	heapSize = n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	heapSort(arr);
	for (int i = 0; i < n; i++)
	{
		cout << arr[i];
		if(i != n - 1)
			cout << ' ';
	}
	return 0;
}