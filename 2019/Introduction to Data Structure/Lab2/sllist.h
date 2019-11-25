#ifndef SLLIST_H
#define SLLIST_H

#include "sllnode.h"
#include <iostream>

using namespace std;

class List
{
private:
	Node* head;
	int size;

public:
	List();
	~List();

	Node* find(int);
	void insert(int, int);
	void remove(int);
	int getSize() const;
	void printAll();
};

#endif