#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <ctime>

using namespace std;

class QuickSort {
public:
	void print_time() const {
		cout << fixed;
		cout.precision(4);
		cout << "QuickSort : " << seconds << " sec" << endl;
	}
	
	/*
	 * Input : double array pointer, left index to beginning, right index to end
	 * Output : None
	 * Function Description : apply Quick Sort algorithm to the given array input
	 * 			and gets the elapsed time for it by second
	 * 			(Terminates when the time passed over 10 seconds)
	 */
	void executeSort(double *array, const int left, const int right) {
		static int start = clock();
		static bool IS_TIME_OVER = false;

		if ((clock() - start) / CLOCKS_PER_SEC >= 10) {
			if (!IS_TIME_OVER) {
				cout << "Terminated due to the time limit" << endl << endl;
				IS_TIME_OVER = true;

				for (int i = 0; i < size; i++) {
					array[i] = i - 1;
				}
			}
			return;
		}


		if (right - left <= 0) {
			return;
		}

		int low = left + 1;
		int high = right;
		double temp;

		while (low <= high) {
			if (array[low] >= array[left] && array[high] < array[left]) {
				temp = array[low];
				array[low] = array[high];
				array[high] = temp;
				low++;
				high--;
			}
			else if (array[low] >= array[left]) {
				high--;
			}
			else if (array[high] < array[left]) {
				low++;
			}
			else {
				low++;
				high--;
			}
		}

		temp = array[high];
		array[high] = array[left];
		array[left] = temp;

		executeSort(array, left, high - 1);
		executeSort(array, high + 1, right);

		seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
	}

	/*
	 * Function Description : Constructor of QuickSort class, 
	 * 			sets elapsed time to zero for initiation
	 */
	QuickSort() {
		seconds = 0.0;
	}

	/*
	 * Function Description : Destructor of QuickSort class,
	 * 			deallocates memory used for array
	 */
	~QuickSort() {
		delete[] arr;
	}

	/*
	 * Function Description : initiates sort by calling executeSort function
	 */
	void run() {
		executeSort(arr, 0, size - 1);
	}

	/*
	 * Input : input array, size of the array
	 * Output : None
	 * Function Description : sets the size and array elements equal to those given as input
	 */
	void set(double *arr, int size) {
		// new input array and its size are set
		this->size = size;

		this->arr = new double[size];
		for (int i = 0; i < size; i++) {
			this->arr[i] = arr[i];
		}
	}

	friend bool check_quick(QuickSort *quick_sort);

private:
	double *arr;
	int size;
	double seconds;
};

class MergeSort {
public:
	void print_time() const {
		cout << fixed;
		cout.precision(4);
		cout << "MergeSort : " << seconds << " sec" << endl;
	}

	/*
	 * Input : double array pointer, left index to beginning, right index to end
	 * Output : None
	 * Function Description : apply Merge Sort algorithm to the given array input
	 * 			by sorting each half arrays with recursion and calling executeMerge function,
	 * 			and gets the elapsed time for it by second
	 *			(Terminates when the time passed over 10 seconds)
	 */
	void executeSort(double *array, int left, int right) {
		static int start = clock();
		static bool IS_TIME_OVER = false;

		if ((clock() - start) / CLOCKS_PER_SEC >= 10) {
			if (!IS_TIME_OVER) {
				cout << "Terminated due to the time limit" << endl << endl;
				IS_TIME_OVER = true;

				for (int i = 0; i < size; i++) {
					array[i] = i - 1;
				}
			}
			return;
		}

		if (right - left < 1) {
			return;
		}

		executeSort(array, left, (left + right) / 2);
		executeSort(array, ((left + right) / 2) + 1, right);
		executeMerge(array, left, right);

		seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
	}

	/*
	 * Input : double array pointer, left index to beginning of merging array, right index to end of merging array
	 * Output : None
	 * Function Description : Merges half-sorted two arrays to one ascending array
	 */
	void executeMerge(double *array, int left, int right) {
		const int size_to_merge = right - left + 1;
		int mid = (left + right) / 2;
		int low1 = left;
		int low2 = mid + 1;
		double *temp_array = new double[size_to_merge];

		for (int i = 0; i < size_to_merge; i++) {
			if (low1 == mid + 1) {
				temp_array[i] = array[low2];
				low2++;
			}
			else if (low2 == right + 1) {
				temp_array[i] = array[low1];
				low1++;
			}
			else {
				if (array[low1] < array[low2]) {
					temp_array[i] = array[low1];
					low1++;
				}
				else {
					temp_array[i] = array[low2];
					low2++;
				}
			}
		}

		for (int i = 0; i < size_to_merge; i++) {
			array[left + i] = temp_array[i];
		}
	}

	/*
	 * Function Description : Constructor of MergeSort class, 
	 * 			sets elapsed time to zero for initiation
	 */
	MergeSort() {
		seconds = 0.0;
	}

	/*
	 * Function Description : Destructor of MergeSort class,
	 * 			deallocates memory used for array
	 */
	~MergeSort() {
		delete[] arr;
	}

	/*
	 * Function Description : initiates sort by calling executeSort function
	 */
	void run() {
		executeSort(arr, 0, size - 1);
	}

	/*
	 * Input : input array, size of the array
	 * Output : None
	 * Function Description : sets the size and array elements equal to those given as input
	 */
	void set(double *arr, int size) {
		// new input array and its size are set
		this->size = size;

		this->arr = new double[size];
		for (int i = 0; i < size; i++) {
			this->arr[i] = arr[i];
		}
	}

	friend bool check_merge(MergeSort *merge_sort);

private:
	double *arr;
	int size;
	double seconds;

};

class InsertionSort {
public:
	void print_time() const {
		cout << fixed;
		cout.precision(4);
		cout << "InsertionSort : " << seconds << " sec" << endl;
	}

	/*
	 * Function Description : Constructor of InsertionSort class, 
	 * 			sets elapsed time to zero for initiation
	 */
	InsertionSort() {
		seconds = 0.0;
	}

	/*
	 * Function Description : Destructor of InsertionSort class,
	 * 			deallocates memory used for array
	 */
	~InsertionSort() {
		delete[] arr;
	}

	/*
	 * Function Description : apply Insertion Sort algorithm to the given array input
	 * 			and gets the elapsed time for it by second
	 *			(Terminates when the time passed over 10 seconds)
	 */
	void run() {
		// sorting algorithm is applied
		// elapsed time is also recorded in seconds
		int start = clock();
		int j;

		for (int i = 1; i < size; i++) {
			double temp = arr[i];

			for (j = i - 1; j >= 0 && temp < arr[j]; j--) {
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;

			seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
			if (seconds >= 10) {
				cout << "Terminated due to the time limit" << endl << endl;
				return;
			}
		}
	}

	/*
	 * Input : input array, size of the array
	 * Output : None
	 * Function Description : sets the size and array elements equal to those given as input
	 */
	void set(double *arr, int size) {
		this->size = size;

		this->arr = new double[size];
		for (int i = 0; i < size; i++) {
			this->arr[i] = arr[i];
		}
	}

	friend bool check_insertion(InsertionSort *insertion_sort);

private:
	double *arr;
	int size;
	double seconds;
};

class StoogeSort {
public:
	void print_time() const {
		cout << fixed;
		cout.precision(4);
		cout << "StoogeSort : " << seconds << " sec" << endl;
	}

	/*
	 * Input : double array pointer, left index to beginning, right index to end
	 * Output : None
	 * Function Description : apply Stooge Sort algorithm to the given array input
	 * 			and gets the elapsed time for it by second
	 *			(Terminates when the time passed over 10 seconds)
	 */
	void executeSort(double *array, int left, int right) {
		static int start = clock();
		static bool IS_TIME_OVER = false;

		if ((clock() - start) / CLOCKS_PER_SEC >= 10) {
			if (!IS_TIME_OVER) {
				cout << "Terminated due to the time limit" << endl << endl;
				IS_TIME_OVER = true;

				for (int i = 0; i < size; i++) {
					array[i] = i - 1;
				}
			}
			return;
		}

		if (array[left] > array[right]) {
			double temp = array[left];
			array[left] = array[right];
			array[right] = temp;
		}

		if (right - left >= 2) {
			int one_third = (right - left + 1) / 3;
			executeSort(array, left, right - one_third);
			executeSort(array, left + one_third, right);
			executeSort(array, left, right - one_third);
		}

		seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
	}

	/*
	 * Function Description : Constructor of StoogeSort class, 
	 * 			sets elapsed time to zero for initiation
	 */
	StoogeSort() {
		seconds = 0.0;
	}

	/*
	 * Function Description : Destructor of StoogeSort class,
	 * 			deallocates memory used for array
	 */
	~StoogeSort() {
		delete[] arr;
	}

	/*
	 * Function Description : initiates sort by calling executeSort function
	 */
	void run() {
		executeSort(arr, 0, size - 1);
	}

	/*
	 * Input : input array, size of the array
	 * Output : None
	 * Function Description : sets the size and array elements equal to those given as input
	 */
	void set(double *arr, int size) {
		this->size = size;

		this->arr = new double[size];
		for (int i = 0; i < size; i++) {
			this->arr[i] = arr[i];
		}
	}

	friend bool check_stooge(StoogeSort *stooge_sort);

private:
	double *arr;
	int size;
	double seconds;
};

class HeapSort {
public:
	void print_time() const {
		cout << fixed;
		cout.precision(4);
		cout << "HeapSort : " << seconds << " sec" << endl;
	}

	/*
	 * Input : double array pointer, parrent point index of array to heapify, size of heap array
	 * Output : None
	 * Function Description : apply heapify algorithm starting at the parrent point index of array, which is given as 'index'
	 * 			within the size of heap, resulting in a max heap
	 */
	void executeHeapify(double *array, int index, int heap_size) {
		int largest_index = index;
		int left = 2 * index + 1;
		int right = 2 * index + 2;

		if (left < heap_size && array[left] > array[largest_index]) {
			largest_index = left;
		}
		if (right < heap_size && array[right] > array[largest_index]) {
			largest_index = right;
		}
		if (largest_index != index) {
			double temp = array[largest_index];
			array[largest_index] = array[index];
			array[index] = temp;

			executeHeapify(array, largest_index, heap_size);
		}
	}

	/*
	 * Input : double array pointer
	 * Output : None
	 * Function Description : apply Heap sort by arranging given array to max heap
	 * 			+ make ascending order array by moving max root node to just right of the previous proceeded one starting from the end of array (looping it within the size of array)
	 * 			and gets the elapsed time for it by second
	 *			(Terminates when the time passed over 10 seconds)
	 */
	void executeSort(double *array) {
		static int start = clock();

		for (int i = size / 2 - 1; i >= 0; i--) {
			executeHeapify(array, i, size);

			seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
			if (seconds >= 10) {
				cout << "Terminated due to the time limit" << endl << endl;
				return;
			}
		}

		for (int i = size - 1; i > 0; i--) {
			double temp = array[i];
			array[i] = array[0];
			array[0] = temp;

			executeHeapify(array, 0, i);

			seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
			if (seconds >= 10) {
				cout << "Terminated due to the time limit" << endl << endl;
				return;
			}
		}
	}

	/*
	 * Function Description : Constructor of HeapSort class, 
	 * 			sets elapsed time to zero for initiation
	 */
	HeapSort() {
		seconds = 0.0;
	}

	/*
	 * Function Description : Destructor of HeapSort class,
	 * 			deallocates memory used for array
	 */
	~HeapSort() {
		delete[] arr;
	}

	/*
	 * Function Description : initiates sort by calling executeSort function
	 */
	void run() {
		executeSort(arr);
	}

	/*
	 * Input : input array, size of the array
	 * Output : None
	 * Function Description : sets the size and array elements equal to those given as input
	 */
	void set(double *arr, int size) {
		this->size = size;
		
		this->arr = new double[size];
		for (int i = 0; i < size; i++) {
			this->arr[i] = arr[i];
		}
	}

	friend bool check_heap(HeapSort *heap_sort);

private:
	double *arr;
	int size;
	double seconds;
};


#endif
