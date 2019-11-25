#include <iostream>
using namespace std;
template <class T>
class heap {
private:
	T* arr;
	int size;
	int number;
public:
	heap(int s) : size(s), number(0), arr(new T[s]) {
		for (int i = 0; i < s; i++)
			arr[i] = NULL;
	}
	void swap(int pos_a, int pos_b);
	void insertData(T data);
	void deleteData();
	T getRoot();
	void print();
};

template <class T>
void heap<T>::swap(int a, int b) {
	T temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}
template <class T>
T heap<T>::getRoot() {
	return arr[0];
}
template <class T>
void heap<T>::print() {
	for (int i = 0; i < number; i++)
		cout << arr[i] << " ";
	cout << endl;
}

template<class T>
void heap<T>::insertData(T data) {
	if (size <= number) {
		cout << "heap is full" << endl;
		return;
	}
	int idx = number;
	int parent = (number - 1) / 2;
	arr[number++] = data;

	while (idx != 0) {
		if (arr[idx] > arr[parent]) {
			swap(idx, parent);
			idx = parent;
			parent = (idx - 1) / 2;
		}
		else break;
	}
}

template<class T>
void heap<T>::deleteData() {
	if (number == 0) {
		cout << "heap is empty" << endl;
		return;
	}
	swap(number - 1, 0);
	arr[number - 1] = NULL;
	number--;
	int idx = 0; int left = 1; int right = 2;
	while (left < number) {
		int max = idx;
		if (arr[left] > arr[max])
			max = left;
		if (right < number && arr[right] > arr[max])
			max = right;
		if (max != idx) {
			swap(idx, max);
			idx = max;
			left = 2 * idx + 1;
			right = 2 * idx + 2;
		}
		else break;
	}
}

template <class T>
void heapSort(T* arr, int size) {
	heap<int> mHeap(size);

	for (int i = 0; i < size; ++i)
		mHeap.insertData(arr[i]);

	for (int i = 0; i < size; ++i) {
		arr[i] = mHeap.getRoot();
		mHeap.deleteData();
	}
}

/*
void main() {
	int a[9] = { 5, 7, 12, 3, 58, 8, 41, 23, 1 };
	heapSort<int>(a, 9);
	for (int i = 0; i < 9; i++)
		cout << a[i] << " ";
	cout << endl;
}
*/