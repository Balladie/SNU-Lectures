#include "dllnode.h"

Node::Node(int n)
{
	num = n;
	next = nullptr;
	prev = nullptr;
}

Node::Node(int n, Node* nextLink, Node* prevLink)
{
	num = n;
	next = nextLink;
	prev = prevLink;
}

void Node::setNext(Node* link)
{
	next = link;
}

Node* Node::getNext()
{
	return next;
}

void Node::setPrev(Node* link)
{
	prev = link;
}

Node* Node::getPrev()
{
	return prev;
}

int Node::getNum()
{
	return num;
}