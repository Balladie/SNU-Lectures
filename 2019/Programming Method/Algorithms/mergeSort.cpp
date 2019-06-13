#include <iostream>

using namespace std;

inline void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void mergeSort(int *arr, int l, int r)
{
	int size = r - l + 1;
	int mid = l + (r - l) / 2;

	if (size <= 1)
		return;

	int* sorted = new int[size];

	mergeSort(arr, l, mid);
	mergeSort(arr, mid + 1, r);

	// Merge
	int i = l;
	int j = mid + 1;
	int k = 0;

	while (i < mid + 1 && j < r + 1)
	{
		if (arr[i] < arr[j])
			sorted[k++] = arr[i++];
		else
			sorted[k++] = arr[j++];
	}

	while (i < mid + 1)
		sorted[k++] = arr[i++];
	while (j < r + 1)
		sorted[k++] = arr[j++];

	for (k = 0; k < size; k++)
	{
		arr[l + k] = sorted[k];
	}

	delete[] sorted;
}

int main()
{
	int n;
	int *arr;

	cin >> n;
	arr = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	mergeSort(arr, 0, n - 1);

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	} cout << endl;

	delete[] arr;
	return 0;
}