#include <iostream>

using namespace std;

template <class T>
void copyArray(T* b, T* a, int n) {
	for (int i = 0; i < n; i++)
		a[i] = b[i];
}
template <class T>
void merge(T* a, int l, int c, int r, T* b) {
	int i = l, j = c;
	for (int k = l; k < r; k++) {
		if (i < c && (j >= r || a[i] >= a[j]))
			b[k] = a[i++];
		else
			b[k] = a[j++];
	}
}

template <class T>
void mergeSort_bottomup(T* a, int n) {
	T* b = new T[n];
	for (int w = 1; w < n; w *= 2) {
		for (int i = 0; i < n; i += 2 * w) {
			merge(a, i, __min(i + w, n), __min(i + 2 * w, n), b);
		}
		copyArray(b, a, n);
	}
}

template <class T>
void split_merge_topdown(T* b, int l, int r, T* a) {
	if (r - l <= 1)
		return;

	const int idx_mid = (r - l) / 2;

	split_merge_topdown(b, l, l + idx_mid, a);
	split_merge_topdown(b, l + idx_mid, r, a);

	for (int i = l; i < r; ++i)
		b[i] = a[i];

	int idx_left = l;
	int idx_right = l + idx_mid;
	int i;

	for (i = l; idx_left < l + idx_mid && idx_right < r; ++i) {
		if (b[idx_left] >= b[idx_right])
			a[i] = b[idx_left++];
		else
			a[i] = b[idx_right++];
	}

	for (; idx_left < l + idx_mid; ++idx_left)
		a[i++] = b[idx_left];
	for (; idx_right < r; ++idx_right)
		a[i++] = b[idx_right];
}
template <class T>
void mergeSort_topdown(T* a, int n) {
	T* b = new T[n];
	copyArray(a, b, n);
	split_merge_topdown(b, 0, n, a);
}

/*
void main() {
	int a[9] = { 5, 7, 12, 3, 58, 8, 41, 23, 1 };
	int* b = new int[9];
	copyArray(a, b, 9);
	cout << "before : ";
	for (int i = 0; i < 9; i++) cout << a[i] << " ";
	cout << endl;
	mergeSort_bottomup<int>(a, 9);
	cout << "after bottom_up : ";
	for (int i = 0; i < 9; i++) cout << a[i] << " ";
	cout << endl;
	cout << "before : ";
	for (int i = 0; i < 9; i++) cout << b[i] << " ";
	cout << endl;
	mergeSort_topdown<int>(b, 9);
	cout << "after top_down : ";
	for (int i = 0; i < 9; i++) cout << b[i] << " ";
	cout << endl;
}
*/