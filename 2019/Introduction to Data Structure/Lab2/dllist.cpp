#include "dllist.h"

List::List()
{
	head = new Node(0, nullptr, nullptr);
	tail = new Node(0, nullptr, head);
	head->setNext(tail);
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

void List::insert(int k, int num)
{
	Node* temp = head;

	if (size < k || k < 0)
		return;

	while (k > 0 && temp->getNext() != nullptr)
	{
		temp = temp->getNext();
		--k;
	}

	Node* newNode = new Node(num, temp->getNext(), temp);
	temp->getNext()->setPrev(newNode);
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
	temp->getNext()->setPrev(curr);
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
		cout << temp->getNum() << " ";
	}

	cout << endl;
}