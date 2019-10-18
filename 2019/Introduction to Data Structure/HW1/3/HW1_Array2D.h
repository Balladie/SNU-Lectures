#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <iostream>
#include <iomanip>

using namespace std;

class Array2D {
public:
	Array2D(int);
	~Array2D();
	friend ostream& operator << (ostream&, const Array2D&);
	void moveRight(int r, int dist);
	void moveLeft(int r, int dist);
	void moveUp(int c, int dist);
	void moveDown(int c, int dist);
	void moveUpRight(int d, int dist);
	void moveDownLeft(int d, int dist);
	void moveUpLeft(int d, int dist);
	void moveDownRight(int d, int dist);
	void swap(int*, int*);
private:
	int** m_array;
	int m_size;
};

#endif