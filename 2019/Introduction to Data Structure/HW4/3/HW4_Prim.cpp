#include "HW4_Prim.h"

template <class T>
void maxHeapify_custom(T* arr, int size_heap, int idx)
{
	int maximum = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < size_heap && arr[left] > arr[maximum])
		maximum = left;

	if (right < size_heap && arr[right] > arr[maximum])
		maximum = right;

	if (maximum != idx)
	{
		swap(arr, idx, maximum);
		maxHeapify_custom(arr, size_heap, maximum);
	}
}

template <class T>
void heapSort_custom(T* arr, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		maxHeapify_custom(arr, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr, 0, i);
		maxHeapify_custom(arr, i, 0);
	}

}

void prim(int n_node, int* n_edge, Edge** adjList, int start_node) {

	// Initialization
	int* S = new int[n_node];
	Edge* T = new Edge[n_node];
	Node* W = new Node[n_node];
	int* W_pos = new int[n_node];

	for (int i = 0; i < n_node; ++i) {
		S[i] = -1;
		W_pos[i] = i;
		W[i].setIdx(i);
		T[i].setIdx(-1);

		if (i == start_node)
			W[i].setDist(0);
		else
			W[i].setDist(INF);
	}

	int curr_node = start_node;
	int j;
	int cnt_T = 0;

	for (int i = 0; i < n_node; ++i) {
		heapSort<Node>(W, W_pos, n_node);

		j = 0;
		while (S[W[j].getIdx()] != -1) {
			++j;
		}

		curr_node = W[j].getIdx();
		S[curr_node] = curr_node;

		for (j = 0; j < n_edge[curr_node]; ++j) {
			int target_node_idx = adjList[curr_node][j].getDest();

			if (W[W_pos[target_node_idx]].getDist() > adjList[curr_node][j].getDist()) {
				W[W_pos[target_node_idx]].setDist(adjList[curr_node][j].getDist());

				for (int t = 0; t < n_node; ++t) {
					if (T[t].getSrc() == target_node_idx || T[t].getIdx() == -1) {
						T[t].setIdx(cnt_T++);
						T[t].setSrc(target_node_idx);
						T[t].setDest(curr_node);
						T[t].setDist(adjList[curr_node][j].getDist());
						break;
					}
				}
			}
		}
	}

	T[n_node - 1].setDist(INF);
	heapSort_custom<Edge>(T, n_node);

	// DO NOT MODIFY - Print the result
	cout << endl << "Result : " << endl;
	cout << "T : " << endl;
	for (int i = 0; i < n_node - 1; i++) {
		if (T[i].getSrc() > T[i].getDest()) {
			int temp = T[i].getSrc();
			T[i].setSrc(T[i].getDest());
			T[i].setDest(temp);
		}
		cout << T[i].getSrc() << " - " << T[i].getDest() << " (" << T[i].getDist() << ")" << endl;
	}

	delete[] S;
	delete[] T;
	delete[] W;
	delete[] W_pos;
}