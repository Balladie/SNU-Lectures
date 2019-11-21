#ifndef HW2_QUEUE_H
#define HW2_QUEUE_H

#include <iostream>

using namespace std;

/* --- DO NOT MODIFY --- */
template <class T>
class Queue
{
private:
	int front;
	int rear;
	T* array;
	int capacity;
public:
	Queue(int c);
	~Queue();
	bool isEmpty() const;
	T getFront() const;
	T getRear() const;
	int getSize() const;
	int getCapacity() const;
	void push(const T& x);
	T pop();
	void print() const;
	void shift(int amount);
};
/* --- DO NOT MODIFY --- */

template <class T>
Queue<T>::Queue(int c) 
{
	if (c > 0)
		array = new T[c];
	else
		array = nullptr;

	front = 0;
	rear = 0;
	capacity = c;
}

template <class T>
Queue<T>::~Queue() 
{
	delete[] array;
}

template <class T>
bool Queue<T>::isEmpty() const 
{
	if (front == rear)
		return true;

	return false;
}

template <class T>
T Queue<T>::getFront() const 
{
	if (isEmpty())
		return T();

	if (front == capacity - 1)
		return array[0];

	return array[front + 1];
}

template <class T>
T Queue<T>::getRear() const 
{
	if (isEmpty())
		return T();

	return array[rear];
}

template <class T>
int Queue<T>::getSize() const 
{
	if (front <= rear)
		return (rear - front);
	else
		return (rear + capacity - front);
}

template <class T>
int Queue<T>::getCapacity() const 
{
	return capacity;
}

template <class T>
void Queue<T>::push(const T& x) 
{
	if (getSize() + 1 == capacity)
	{
		int size = getSize();

		T* tmp = new T[size];

		for (int i = 0; i < size; ++i)
		{
			tmp[i] = array[(front + 1 + i) % capacity];
		}

		delete[] array;
		array = new T[2 * capacity];

		for (int i = 0; i < size; ++i)
		{
			array[i + 1] = tmp[i];
		}

		delete[] tmp;
		capacity *= 2;
		front = 0;
		rear = size;
	}

	rear = (rear + 1) % capacity;

	array[rear] = x;
}

template <class T>
T Queue<T>::pop() 
{
	if (isEmpty())
		return T();

	T data = getFront();

	if (front == capacity - 1)
		front = 0;
	else
		++front;

	return data;
}

template <class T>
void Queue<T>::print() const 
{
	cout << "[";

	if (!isEmpty())
	{
		for (int i = front + 1; i != rear; i = (i + 1) % capacity)
		{
			cout << array[i] << ", ";
		}
		cout << array[rear];
	}

	cout << "]" << endl;
}

template <class T>
void Queue<T>::shift(int amount) 
{
	if (getSize() == 0)
		return;

	if (amount >= 0)
	{
		amount %= getSize();

		for (int i = 0; i < getSize() - amount; ++i)
		{
			push(pop());
		}
	}
	else
	{
		amount %= getSize();

		for (int i = 0; i < (-1) * amount; ++i)
		{
			push(pop());
		}
	}
}

#endif