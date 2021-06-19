#pragma once

template <typename K, typename V>
class HashNode 
{
private:
	K key;
	V value;

	HashNode* next;

public:
	HashNode(const K& key, const V& value);
	const K getKey() const;
	const V getValue() const;
	HashNode* getNext() const;
	void setNext(HashNode* next);
	void setValue(V& value);
	void print() const;
	
};
template <typename K, typename V>
HashNode<K, V>::HashNode(const K& key, const V& value)
{
	this->key = key;
	this->value = value;
	this->next = nullptr;
}
template <typename K, typename V>
const K HashNode<K,  V>::getKey() const
{
	return key;
}
template <typename K, typename V>
const V HashNode<K, V>::getValue() const
{
	return value;
}

template <typename K, typename V>
void HashNode< K,  V>::setNext(HashNode* next)
{
	this->next = next;
}
template <typename K, typename V>
void HashNode< K,  V>::setValue(V& value)
{
	this->value = value;
}
template <typename K, typename V>
void HashNode<K,  V>::print() const
{
	std::cout << key << " : " << value << " ";
}
