#include <iostream>

using namespace std;

inline void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void merge(int *arr, int l, int mid, int r)
{
	int size = r - l + 1;

	if (size <= 1)
		return;

	int* sorted = new int[size];

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

void mergeSort(int* arr, int l, int r)
{
	int n = r - l + 1;

	for (int i = 1; i < n; i *= 2) // size
	{
		for (int j = 0; j < n; j += 2 * i) // cur
		{
			int mid = j + i - 1;

			if (j + 2 * i >= n)
				merge(arr, j, mid, n - 1);
			else
				merge(arr, j, mid, j + 2 * i - 1);
		}
	}
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