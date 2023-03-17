#pragma once
#include <utility>
#include <functional>
#include "myexception.h"

/**
* @brief	A hash table, every bucket in which can only hold one pair.
* Use linear probing.
* @see		"HashChains.h" for a hash chain, every bucket in which can hold all pairs.
*/
template<class K, class E>
class hashTable
{
public:
	hashTable(int theDivisor = 1);
	int size() { return dSize; }
	bool empty() { return dSize == 0; }
public:
	/**
	* @brief	Linear probing.
	* Search a hash table with public address for a pair with key "theKey".
	* @param	theKey The target key.
	* @return	If the matched key exists, return it's position; 
	*			Otherwise, return an available position where is not full.
	*			If there is no available position, return home bucket.
	*/
	int search(const K& theKey) const;
	/**
	* @brief	Return the pointer of matched pair.
	* 
	* @param	theKey The target key.
	* @return	If the matched piar exists, return it's position;
	*			Otherwise, return nullptr.
	*/
	std::pair<const K, E>* find(const K& theKey) const;
	/**
	* @brief	Insert thePair to the dictionary;
	* If there exists a pair with the same key, insert the pair in an available location.
	* @param	thePair The pair to insert.
	*/
	void insert(const std::pair<const K, E>& thePair);
	/**
	* @brief	Erase the pair with the key "theKey".
	* 
	* @param	theKey The target key.
	*/
	void erase(const K& theKey);
private:
	std::pair<const K, E>** table; // table[i] is the pointer of one pair.
	std::hash<K> hash;
	int dSize;
	int divisor;
};

template<class K,class E>
hashTable<K, E>::hashTable(int theDivisor) : divisor(theDivisor) {
	divisor = theDivisor;
	dSize = 0;
	// Allocate and initialize hash table array.
	table = new std::pair<const K, E>*[divisor];
	for (int i = 0; i < divisor; i++) {
		table[i] = nullptr;
	}
}

template<class K,class E>
int hashTable<K,E>::search(const K& theKey) const {
	int i = static_cast<unsigned int>(hash(theKey) % divisor); // Home bucket.
	int j = i; // Start from the home bucket.
	// Loop until j goes around from i to i.
	do {
		if (table[j] == nullptr || table[j]->first == theKey) {
			return j;
		}
		// Next bucket.
		j = (j + 1) % divisor;
	} while (j != i);
	// The matched key exists, return it's location.
	return j;
}

template<class K,class E>
std::pair<const K, E>* hashTable<K, E>::find(const K& theKey) const {
	int b = search(theKey);
	// Judge whether table[b] is matched piar.
	if (table[b] == nullptr || table[b]->first != theKey) {
		return nullptr;
	}
	return table[b];
}

template<class K,class E>
void hashTable<K, E>::insert(const std::pair<const K, E>& thePair) {
	int b = search(thePair.first);
	// IF: the bucket is empty.
	if (table[b] == nullptr) {
		table[b] = new std::pair<const K, E>(thePair);
		dSize++;
	}
	// IF: the bucket is full or there is not such bucket.
	else {
		if (table[b]->first == thePair.first) {
			table[b]->second = thePair.second;
		}
		else {
			throw hashTableFull();
		}
	}
}

template<class K,class E>
void hashTable<K, E>::erase(const K& theKey) {
	std::pair<const K, E>* theBucket = find(theKey);
	// IF: "theKey" is not found.
	if (theBucket == nullptr) {
		printf("Not found.\n");
		return;
	}
	// Delete the pair.
	delete theBucket; theBucket = nullptr;
	// Create the home bucket.
	int home = static_cast<unsigned int>(hash(theKey) % divisor);
	// Create double pointer for further movement.
	int i, j; i = j = home;
	do {
		j = (j + 1) % divisor;
		if (table[j] == nullptr) {
			break;
		}
		// IF: the pair in the bucket does not belong to the bucket.
		if (static_cast<unsigned int>(hash(table[j]->first) % divisor) != j) {
			table[i] = table[j];
			table[j] = nullptr;
			i = j;
		}
	} while (j != home);
}