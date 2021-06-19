#pragma once
#include "HashNode.h"
#include <string>
#include<fstream>
#include<iostream>



template <typename K, typename V>
class HashMap
{
private:
	HashNode<K, V>** table;
	size_t size;
	

	void copy(const HashMap& rhs);
	void clear();
	int hashFunc(const K& key);
		
	
	

public:
	
	HashMap();
	HashMap(const unsigned& size);
	HashMap(const HashMap& rhs);
	HashMap& operator=(const HashMap& rhs);
	~HashMap();
	
	const size_t& getSize() const;
	bool isValid(const K& key, const V& value);
	V getValue(const K& key); 
	void addNewValue(const K& key, V value);
	void removeValue(const K& key);
	void printHashTable() const;
	void printHashTableToFile(std::ostream& fileName) const;
	V& operator[] (const K& key);
	
	void toArray(std::vector<V>& result) const;

	
	
	

};
template <typename K, typename V>

void HashMap<K, V>::printHashTableToFile(std::ostream& fileName) const
{
	for (unsigned i = 0; i < size; ++i)
	{
		HashNode<K, V>* cur = table[i];

		if (cur != nullptr)
		{
			fileName << '\n';
		}

		while (cur != nullptr)
		{
			fileName << cur->key << " : " << cur->value << " ";
			cur = cur->getNext();
		}
	}
}
 //помощни функции
template <typename K, typename V>
void HashMap<K, V>:: copy(const HashMap& rhs)
{
	this->table = new HashNode * [rhs.getSize()];
	this->size = rhs.getSize();
	for (unsigned i = 0; i < size; ++i) 
	{
		table[i] = rhs.table[i]; 
		HashNode<K, V>* copy = rhs.table[i]; 
		HashNode<K, V>* cur = table[i];
		while (copy->getNext() != nullptr)
		{
			cur->setNext(new HashNode(copy->getNext())); 
			copy = copy->getNext();
			cur = cur->getNext();
		}
	}
}
template <typename K, typename V>
void HashMap<K,  V>::clear()
{
	for (unsigned i = 0; i < size; ++i)
	{
		HashNode<K, V>* line = table[i]; 
		while (line != nullptr)
		{
			HashNode<K, V>* prev = line; 

			line = line->getNext();
			delete prev;
		}
		table[i] = nullptr;
	}

	delete[] table;
} 
template <typename K, typename V>
HashMap< K, V >::HashMap()
{
	this->size = 16;
	table = new HashNode<K, V> * [size];
	for (size_t i = 0; i < size; i++)
	{
		table[i] = nullptr;
	}
}


template <typename K, typename V >
HashMap< K,  V>::HashMap(const unsigned& size)
{
	table = new HashNode<K, V> * [size];
	this->size = size;
	for (size_t i = 0; i < size; i++)
	{
		table[i] = nullptr;
	}
} 
template <typename K, typename V>
HashMap< K,  V>::HashMap(const HashMap& rhs)
{
	copy(rhs);
}
template <typename K, typename V>
HashMap<K, V>& HashMap<K, V>::operator=(const HashMap& rhs)
{
	if (this != &rhs)
	{
		clear();
		copy(rhs);
	}

	return *this;
}
template <typename K, typename V >
HashMap< K,  V>::~HashMap()
{
	clear();
}
template<typename K, typename V>
const size_t& HashMap<K, V>::getSize() const
{
	return this->size;
}

//the other functions
/*
template <typename K, typename V, typename F >
unsigned& const HashMap< K, V, F > ::getSize() const
{
	return size;
}*/
template <typename K, typename V>
bool HashMap< K, V >::isValid(const K& key, const V& value)
{
	int hashValue = hashFunc(key);
	HashNode<K, V>* line = table[hashValue];

	while (line != nullptr)
	{
		if (line->getKey() == key && line->getValue() == value)
		{
			return true;
		}
		line = line->getNext();
	}

	return false;
}
template <typename K, typename V>
V HashMap<K, V>::getValue(const K& key)
{
	int hashValue = hashFunc(key);
	V value;
	HashNode<K, V>* line = table[hashValue];

	while (line != nullptr)
	{
		if (line->getKey() == key)
		{
			value = line->getValue();
			break;
		}
		line = line->getNext();
	}

	return value;
}

template <typename K, typename V > 
void HashMap<K,  V>::addNewValue(const K& key, V value)
{
	int hashValue = hashFunc(key); 
	HashNode<K, V>* prev = nullptr;
	HashNode<K, V>* line = table[hashValue];

	while (line != nullptr && line->getKey() != key)
	{
		prev = line;
		line = line->getNext();
	}

	if (line == nullptr)
	{
		line = new HashNode<K, V>(key, value);

		if (prev == nullptr)
		{
			table[hashValue] = line;
		}
		else
		prev->setNext(line);
		
	}
	else
	{
		line->setValue(value);
	}

}
template <typename K, typename V >
void HashMap<K, V>::removeValue(const K& key)
{
	int hashValue = hashFunc(key);
	HashNode<K, V>* prev = nullptr;
	HashNode<K, V>* line = table[hashValue];

	while (line != nullptr && line->getKey() != key)
	{
		prev = line;
		line = line->getNext();
	}

	if (line == nullptr) 
	{
		return;
	}
	else
	{
		if (prev == nullptr) 
		{
			table[hashValue] = line->getNext();
		}
		else
		{
			prev->setNext(line->getNext());

			delete line;
		}
	}
}
template <typename K, typename V>
void HashMap< K,  V >::printHashTable() const
{
	for (unsigned i = 0; i < size; ++i)
	{
		HashNode<K, V>* cur = table[i];

		if (cur != nullptr)
		{
			std::cout << std::endl;
		}

		while (cur != nullptr)
		{
			cur->print();
			cur = cur->getNext();
		}
	}
}
template<typename K, typename V>
inline V& HashMap<K, V>::operator[](const K& key)
{
	V result = getValue(key);
	return result;
}
template<typename K, typename V>
inline void HashMap<K, V>::toArray(std::vector<V>& result) const
{
	for (unsigned i = 0; i < size; ++i)
	{
		HashNode<K, V>* cur = table[i];

		result.push_back(cur->value);
	}
}
/*
template <typename K, typename V>
HashMap< K, V >& HashMap<K, V>::operator[](K const& key)
{
	return HashMap(this, key);
} */
template <typename K, typename V>
int HashMap< K, V >::hashFunc(const K& key)

{
	int count = 0;
	for (int k = 0; k < key.length(); ++k)
		count = count + int(key[k]);
	return  count% size;
}


