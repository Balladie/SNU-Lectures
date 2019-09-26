#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

template<typename T>
class List {
private:
	class Node {
	public:
		Node()
		{
			next = NULL;
		}
		Node(T newData)
		{
			data = newData;
			next = NULL;
		}

		T data;
		Node * next;
	};

public:
	List() : head(new Node()), size(0) {}

	~List()
	{
		Node * curr = getHead();

		while (curr != NULL)
		{
			Node * tmpToDel = curr;
			curr = curr->next;
			delete tmpToDel;
		}
	}

	// k-jumping to find
	Node * find(Node *curr, int k)
	{
		if (k == 0 || curr == NULL)
			return curr;
		else
			return find(curr->next, k - 1);
	}

	// insert a node in k-th position
	void insert(int loc, T data)
	{
		Node * newNode = new Node(data);

		Node * curr = find(head, loc - 1);
		newNode->next = curr->next;
		curr->next = newNode;

		size++;
	}

	void insertAtFront(Node * &curr, T data)
	{
		Node * toAdd = new Node(data);

		toAdd->next = curr;
		curr = toAdd;
		++size;
	}

	void remove(Node * curr)
	{
		Node * tmp = curr->next;

		curr->data = tmp->data;
		curr->next = tmp->next;

		delete tmp;
		size--;
	}

	int getSize() const
	{
		return size;
	}

	T & getData(int loc)
	{
		Node * tmp = find(head, loc);
		return tmp->data;
	}

	Node * & getHead()
	{
		return head;
	}

	void printReverse(Node * curr)
	{
		if (curr != NULL && curr != head)
		{
			printReverse(curr->next);
			cout << curr->data << " ";
		}
	}

private:
	Node * head;
	int size;
};

int main()
{
	List<int> list;
	
	list.insert(1, 6);
	list.insert(1, 9);
	list.insertAtFront(list.getHead()->next, 4);

	cout << list.getSize() << endl;
	list.printReverse(list.getHead()->next);

	system("pause");
	return 0;
}