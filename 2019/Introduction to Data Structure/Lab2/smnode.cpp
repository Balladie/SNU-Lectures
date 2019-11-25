#include "smnode.h"

Node::Node(int idx, int n)
{
	num = n;
	index = idx;
	next = nullptr;
}

Node::Node(int idx, int n, Node* link)
{
	num = n;
	index = idx;
	next = link;
}

void Node::setNext(Node* link)
{
	next = link;
}

Node* Node::getNext()
{
	return next;
}

int Node::getNum()
{
	return num;
}

int Node::getIndex()
{
	return index;
}