#ifndef DLLIST_H
#define DLLIST_H

#include "dllnode.h"
#include <iostream>

using namespace std;

class List
{
private:
	Node* head, *tail;
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