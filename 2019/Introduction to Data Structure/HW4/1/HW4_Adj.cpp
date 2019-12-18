#include "HW4_Adj.h"

void tokenize(const string& str, vector<string>& tokens, const string& delimiters = " ")
{
	tokens.clear();
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

void adjReader(string filename, int& n_node, int**& adj) {

	ifstream file(filename);
	stringstream buffer;
	buffer << file.rdbuf();
	string input = buffer.str();

	vector<string> vInput;
	tokenize(input, vInput, "\n");

	n_node = vInput.size();
	adj = new int* [n_node];
	for (int i = 0; i < n_node; i++)
		adj[i] = new int[n_node];

	vector<string> vLine;
	for (int i = 0; i < n_node; i++) {
		tokenize(vInput[i], vLine, ",");

		for (int j = 0; j < n_node; j++)
			adj[i][j] = stoi(vLine[j]);

	}

}

void matrixToList(int n_node, int** adjMatrix, int* n_edge, Edge** adjList) {
	int cnt;
	int cnt_idx = 0;

	for (int i = 0; i < n_node; ++i) {
		n_edge[i] = 0;

		for (int j = 0; j < n_node; ++j) {
			if (adjMatrix[i][j] > 0) {
				++(n_edge[i]);
			}
		}
	}

	for (int i = 0; i < n_node; ++i) {
		adjList[i] = new Edge[n_edge[i]];
		cnt = 0;

		for (int j = 0; j < n_node; ++j) {
			if (adjMatrix[i][j] > 0) {
				adjList[i][cnt].setIdx(cnt_idx++);
				adjList[i][cnt].setSrc(i);
				adjList[i][cnt].setDest(j);
				adjList[i][cnt].setDist(adjMatrix[i][j]);
				++cnt;
			}
		}
	}
}