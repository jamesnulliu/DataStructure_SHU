#pragma once
#include <utility>
#include <functional>
#include "myexception.h"
#include <cmath>

/**
* @brief	A hash table, every bucket in which can only hold one pair.
* Use quadratic probing. https://www.cnblogs.com/terryzh/p/15106588.html
* @see		"HashChains.h" for a hash chain, every bucket in which can hold all pairs.
*/
template<class K, class E>
class hashTable_QuadradicProbing
{
public:
	hashTable_QuadradicProbing(int theDivisor = 1);
	int size() { return dSize; }
	bool empty() { return dSize == 0; }
public:
	/**
	* @brief	quadratic probing.
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
hashTable_QuadradicProbing<K, E>::hashTable_QuadradicProbing(int theDivisor) {
	divisor = theDivisor;
	dSize = 0;
	// Allocate and initialize hash table array.
	table = new std::pair<const K, E>*[divisor];
	for (int i = 0; i < divisor; i++) {
		table[i] = nullptr;
	}
}

template<class K, class E>
int hashTable_QuadradicProbing<K, E>::search(const K& theKey) const {
	int home = static_cast<int>(hash(theKey) % divisor);
	int j = home;
	double count = 1.0;
	do {
		if (table[j] == nullptr || table[j]->first == theKey) {
			break;
		}
		j = (home + pow(-1, (int)(count + 0.5) % 2) * (int)count * (int)count) % divisor;
		count += 0.5;
	} while (j != home);
	return j;
}

template<class K,class E>
std::pair<const K, E>* hashTable_QuadradicProbing<K,E>::find(const K& theKey) const {
	int theBucket = search(theKey);
	// Judge whether table[b] is matched piar.
	if (table[theBucket] == nullptr || table[theBucket]->first != theKey) {
		return nullptr;
	}
	return table[theBucket];
}

template<class K,class E>
void hashTable_QuadradicProbing<K, E>::insert(const std::pair<const K, E>& thePair) {
	int theBucket = search(thePair.first);
	// IF: the bucket is empty.
	if (table[theBucket] == nullptr) {
		table[theBucket] = new std::pair<K, E>(thePair);
	}
	else {
		if (table[theBucket]->first == thePair.first) {
			table[theBucket]->second = thePair.second;
		}
		else {
			throw hashTableFull;
		}
	}
}

template<class K,class E>
void hashTable_QuadradicProbing<K, E>::erase(const K& theKey) {
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
	int count = 1;
	do {
		j = (home + pow(-1, ((int)count + 1) % 2) * (int)count * (int)count) % divisor;
		count += 0.5;
		if (table[j] == nullptr) {
			break;
		}
		// IF: the pair in the bucket does not belong to the bucket.
		if (static_cast<int>(hash(table[j]->first) % divisor) != j) {
			table[i] = table[j];
			table[j] = nullptr;
			i = j;
		}
	} while (j != home);
}