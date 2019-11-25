#ifndef SLLNODE_H
#define SLLNODE_H

class Node
{
private:
	int num;
	Node* next;

public:
	Node(int);
	Node(int, Node*);
	void setNext(Node*);
	Node* getNext();
	int getNum();
};

#endif