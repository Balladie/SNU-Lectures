#include "smlist.h"

List::List()
{
	head = new Node(0, 0, nullptr);
	size = 0;
}

List::~List()
{
	Node* curr = head;

	while (curr != nullptr)
	{
		Node* temp = curr->getNext();
		delete curr;
		curr = temp;
	}
}

Node* List::find(int num)
{
	Node* temp = head;

	while (temp->getNext() != nullptr)
	{
		temp = temp->getNext();

		if (temp->getNum() == num)
			return temp;
	}

	return nullptr;
}

void List::insert(int idx, int n)
{
	Node* temp = head;

	if (idx < 0)
		return;

	while (temp->getNext() != nullptr && temp->getNext()->getIndex() <= idx)
	{
		temp = temp->getNext();
	}

	Node* newNode = new Node(idx, n, temp->getNext());
	temp->setNext(newNode);
	++size;
}

void List::remove(int k)
{
	Node* curr = head;

	if (size < k || k < 0)
		return;

	while (k > 0 && curr->getNext() != nullptr)
	{
		curr = curr->getNext();
		--k;
	}

	Node* temp = curr->getNext();
	curr->setNext(temp->getNext());
	delete temp;
}

int List::getSize() const
{
	return size;
}

void List::printAll()
{
	Node* temp = head;

	while (temp->getNext() != nullptr)
	{
		temp = temp->getNext();
		cout << "(" << temp->getIndex() << ", " << temp->getNum() << ") ";
	}

	cout << endl;
}