#include "HW4_Dijkstra.h"

inline int min(int a, int b) {
	return a < b ? a : b;
}

void dijkstra(int n_node, int* n_edge, Edge** adjList, int start_node) {

	// Initialization
	int* N = new int[n_node];
	Edge* T = new Edge[n_node];
	Node* D = new Node[n_node];
	int* D_pos = new int[n_node];

	for (int i = 0; i < n_node; ++i) {
		N[i] = -1;
		D_pos[i] = i;
		D[i].setIdx(i);
		T[i].setIdx(-1);

		if (i == start_node)
			D[i].setDist(0);
		else
			D[i].setDist(INF);
	}

	int curr_node = start_node;
	int j;
	int cnt_T = 0;

	for (int i = 0; i < n_node; ++i) {
		heapSort<Node>(D, D_pos, n_node);

		j = 0;
		while (N[D[j].getIdx()] != -1)
			++j;

		curr_node = D[j].getIdx();
		N[curr_node] = curr_node;

		for (j = 0; j < n_edge[curr_node]; ++j) {
			int target_node_idx = adjList[curr_node][j].getDest();
			D[D_pos[target_node_idx]].setDist(min(D[D_pos[target_node_idx]].getDist(), D[D_pos[curr_node]].getDist() + adjList[curr_node][j].getDist()));

			if (D[D_pos[target_node_idx]].getDist() > D[D_pos[curr_node]].getDist() + adjList[curr_node][j].getDist()) {
				D[D_pos[target_node_idx]].setDist(D[D_pos[curr_node]].getDist() + adjList[curr_node][j].getDist());

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

	// DO NOT MODIFY - Print the result
	cout << endl << "Result : " << endl;

	cout << endl << "D : " << endl;
	for (int i = 0; i < n_node; i++) {
		D[D_pos[i]].print(); cout << endl;
	}

	delete[] N;
	delete[] T;
	delete[] D;
	delete[] D_pos;
}
