#ifndef SMNODE_H
#define SMNODE_H

class Node
{
private:
	int num, index;
	Node* next;

public:
	Node(int, int);
	Node(int, int, Node*);
	void setNext(Node*);
	Node* getNext();
	int getNum();
	int getIndex();
};

#endif