#include <iostream>
#include "Sort.h"

using namespace std;

bool check_quick(QuickSort *quick_sort) {
	if (quick_sort->arr[0] == -1) {
		return false;
	}

	for (int i = 1; i < quick_sort->size; i++) {
		if (quick_sort->arr[i - 1] > quick_sort->arr[i]) {
			return false;
		}
	}
	return true;
}

bool check_merge(MergeSort *merge_sort) {
	if (merge_sort->arr[0] == -1) {
		return false;
	}

	for (int i = 1; i < merge_sort->size; i++) {
		if (merge_sort->arr[i - 1] > merge_sort->arr[i]) {
			return false;
		}
	}
	return true;
}

bool check_insertion(InsertionSort *insertion_sort) {
	if (insertion_sort->arr[0] == -1) {
		return false;
	}

	for (int i = 1; i < insertion_sort->size; i++) {
		if (insertion_sort->arr[i - 1] > insertion_sort->arr[i]) {
			return false;
		}
	}
	return true;
}

bool check_stooge(StoogeSort *stooge_sort) {
	if (stooge_sort->arr[0] == -1) {
		return false;
	}

	for (int i = 1; i < stooge_sort->size; i++) {
		if (stooge_sort->arr[i - 1] > stooge_sort->arr[i]) {
			return false;
		}
	}
	return true;
}

bool check_heap(HeapSort *heap_sort) {
	if (heap_sort->arr[0] == -1) {
		return false;
	}

	for (int i = 1; i < heap_sort->size; i++) {
		if (heap_sort->arr[i - 1] > heap_sort->arr[i]) {
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	double *input_array;
	int n;
	cin >> n;

	// generate random numbers and apply each sorting algorithms
	input_array = new double[n];
	for (int i = 0; i < n; i++) {
		input_array[i] = (double)(rand() % 1000);
	}
	cout << endl;

	// QuickSort
	QuickSort *quick_sort = new QuickSort();
	quick_sort->set(input_array, n);
	quick_sort->run();
	quick_sort->print_time();

	if (check_quick(quick_sort)) {
		cout << "QuickSort is validated" << endl;
	}
	cout << endl;
	delete quick_sort;

	
	// MergeSort
	MergeSort *merge_sort = new MergeSort();
	merge_sort->set(input_array, n);
	merge_sort->run();
	merge_sort->print_time();

	if (check_merge(merge_sort)) {
		cout << "MergeSort is validated" << endl;
	}
	cout << endl;
	delete merge_sort;

	
	// InsertionSort
	InsertionSort *insertion_sort = new InsertionSort();
	insertion_sort->set(input_array, n);
	insertion_sort->run();
	insertion_sort->print_time();

	if (check_insertion(insertion_sort)) {
		cout << "InsertionSort is validated" << endl;
	}
	cout << endl;
	delete insertion_sort;

	// StoogeSort
	StoogeSort *stooge_sort = new StoogeSort();
	stooge_sort->set(input_array, n);
	stooge_sort->run();
	stooge_sort->print_time();

	if (check_stooge(stooge_sort)) {
		cout << "StoogeSort is validated" << endl;
	}
	cout << endl;
	delete stooge_sort;


	// HeapSort
	HeapSort *heap_sort = new HeapSort();
	heap_sort->set(input_array, n);
	heap_sort->run();
	heap_sort->print_time();

	if (check_heap(heap_sort)) {
		cout << "HeapSort is validated" << endl;
	}
	cout << endl;
	delete heap_sort;


	return 0;
}
