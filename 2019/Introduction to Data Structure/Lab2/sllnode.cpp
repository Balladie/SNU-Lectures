#include "sllnode.h"

Node::Node(int n)
{
	num = n;
	next = nullptr;
}

Node::Node(int n, Node* link)
{
	num = n;
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