#ifndef HW3_HASH_H
#define HW3_HASH_H

#include <iostream>
using namespace std;

template <class V>

class HashTable {
private:
	template <class V>
	class HashNode {
	public:
		int key;
		V value;
		HashNode(int key_, V value_) {
			key = key_;
			value = value_;
		}
	};
	HashNode<V>** table;
	int capacity;
	int number;
	HashNode<V>* dummy;

public:
	HashTable(int cap);
	~HashTable();
	void tableDoubling();
	int hashFunction(int key) {
		return key % capacity;
	}
	void insertNode(int key, V value);
	V deleteNode(int key);
	V search(int key);
	void display();
};

template <class V>
HashTable<V>::HashTable(int cap) {
	capacity = cap;
	number = 0;
	dummy = new HashNode<V>(-1, NULL);

	table = new HashNode<V> * [capacity];
	for (int i = 0; i < capacity; ++i)
		table[i] = nullptr;
}


template <class V>
HashTable<V>::~HashTable() {
	for (int i = 0; i < capacity; ++i)
	{
		if (table[i] != nullptr && table[i] != dummy)
			delete table[i];
	}

	delete dummy;
}

template <class V>
void HashTable<V>::tableDoubling() {
	HashNode<V>** tmp_table = new HashNode<V> * [2 * capacity];
	capacity *= 2;

	for (int i = 0; i < capacity; ++i)
		tmp_table[i] = nullptr;

	for (int i = 0; i < capacity / 2; ++i) {
		if (table[i] != nullptr && table[i] != dummy) {
			int idx_new = hashFunction(table[i]->key);

			while (tmp_table[i] != nullptr) {
				if (idx_new == capacity - 1)
					idx_new = 0;
				else
					++idx_new;
			}

			tmp_table[idx_new] = new HashNode<V>(table[i]->key, table[i]->value);
		}
	}

	for (int i = 0; i < capacity / 2; ++i) {
		if (table[i] != nullptr && table[i] != dummy)
			delete table[i];
	}

	table = tmp_table;
}

template <class V>
void HashTable<V>::insertNode(int key, V value) {
	int idx_to_add = hashFunction(key);
	bool same_key_detect = false;

	while (table[idx_to_add] != nullptr && table[idx_to_add] != dummy) {
		if (table[idx_to_add]->key == key) {
			same_key_detect = true;
			break;
		}
		if (idx_to_add == capacity - 1)
			idx_to_add = 0;
		else
			++idx_to_add;
	}

	if (same_key_detect) {
		table[idx_to_add]->value = value;
	}
	else {
		table[idx_to_add] = new HashNode<V>(key, value);
		++number;

		if (number > capacity / 2) {
			tableDoubling();
		}
	}
}

template <class V>
V HashTable<V>::deleteNode(int key) {
	int idx_to_find = hashFunction(key);

	while (table[idx_to_find] != nullptr) {
		if (table[idx_to_find]->key == key) {
			V val_to_ret = table[idx_to_find]->value;

			delete table[idx_to_find];
			table[idx_to_find] = dummy;

			--number;
			return val_to_ret;
		}

		if (idx_to_find == capacity - 1)
			idx_to_find = 0;
		else
			++idx_to_find;
	}

	cout << "key <" << key << "> does not exist." << endl;
	return NULL;
}

template <class V>
V HashTable<V>::search(int key) {
	int idx_to_find = hashFunction(key);

	while (table[idx_to_find] != nullptr) {
		if (table[idx_to_find]->key = key)
			return table[idx_to_find]->value;

		if (idx_to_find == capacity - 1)
			idx_to_find = 0;
		else
			++idx_to_find;
	}

	return NULL;
}

template <class V>
void HashTable<V>::display() {
	cout << "Capacity : " << capacity << ", The number of nodes : " << number << endl;

	for (int i = 0; i < capacity; ++i) {
		if (table[i] != nullptr && table[i] != dummy) {
			cout << "address " << i << ", key = " << table[i]->key << ", value = " << table[i]->value << endl;
		}
	}
	cout << endl;
}

#endif
