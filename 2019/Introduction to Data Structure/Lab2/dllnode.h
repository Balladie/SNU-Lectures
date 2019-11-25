#ifndef DLLNODE_H
#define DLLNODE_H

class Node
{
private:
	int num;
	Node* next, *prev;

public:
	Node(int);
	Node(int, Node*, Node*);
	void setNext(Node*);
	Node* getNext();
	void setPrev(Node*);
	Node* getPrev();
	int getNum();
};

#endif