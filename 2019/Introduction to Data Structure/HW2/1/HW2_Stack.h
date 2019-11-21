#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

/* --- DO NOT MODIFY --- */
template <class T>
class Stack {
private:
	class Node {
	private:
		Node* next;
		T data;

	public:
		Node(T d) {
			data = d;
		}
		Node(T d, Node* n) {
			data = d;
			next = n;
		}
		void setNext(Node* n) {
			next = n;
		}
		Node* getNext() {
			return next;
		}
		T getData() {
			return data;
		}
	};

private:
	Node* top;

public:
	Stack();
	~Stack();
	bool isEmpty() const;
	T getTop() const;
	int getSize() const;
	void push(const T&);
	T pop();
	void print() const;

};
/* --- DO NOT MODIFY --- */

template <class T>
Stack<T>::Stack() 
{
	top = nullptr;
}

template <class T>
Stack<T>::~Stack() 
{
	Node* curr = top;
	Node* tmp;

	while (curr != nullptr)
	{
		tmp = curr->getNext();
		delete curr;
		curr = tmp;
	}
}

template <class T>
bool Stack<T>::isEmpty() const 
{
	if (top == nullptr)
		return true;

	return false;
}

template <class T>
T Stack<T>::getTop() const 
{
	if (isEmpty())
		return T();

	return top->getData();
}

template <class T>
int Stack<T>::getSize() const 
{
	Node* curr = top;
	int size = 0;

	while (curr != nullptr)
	{
		++size;
		curr = curr->getNext();
	}

	return size;
}

template <class T>
void Stack<T>::push(const T& newData) 
{
	Node* nodeToPush = new Node(newData, top);
	top = nodeToPush;
}

template <class T>
T Stack<T>::pop() 
{
	if (isEmpty())
		return T();

	T poppedData = top->getData();
	Node* tmp = top;
	top = top->getNext();
	delete tmp;

	return poppedData;
}

template <class T>
void Stack<T>::print() const 
{
	Node* curr = top;

	cout << "[";

	if (isEmpty())
	{
		cout << "]" << endl;
		return;
	}

	while (curr->getNext() != nullptr)
	{
		cout << curr->getData() << ", ";
		curr = curr->getNext();
	}

	cout << curr->getData() << "]" << endl;
}

#endif