#pragma once
#pragma once
#include <utility>
#include <functional>
#include "SortedChain.h"
#include "myexception.h"

template<class K,class E>
class hashChains
{
public:
	hashChains(int theDivisor = 1);
	int size() { return dSize; }
	bool empty() { return dSize == 0; }
public:
	/**
	* @brief	Find a pair with key "theKey".
	* 
	* @param	theKey The target key.
	* @return	IF found, return the pointer of the pair;
	*			IF not found, return nullptr.
	*/
	std::pair<const K, E>* find(const K& theKey) const;
	/**
	* @brief	Insert "thePair" to hash chain.
	* Multiple pairs can fall into the same bucket if their hash value % division is the same.
	* Rewirte can happen in single bucket.
	* @param	thePair The pair to insert.
	*/
	void insert(const std::pair<const K, E>& thePair);
	void erase(const K& theKey);
private:
	sortedChain<K, E>* table;
	std::hash<K> hash;
	int dSize;
	int divisor;
};

template<class K,class E>
hashChains<K, E>::hashChains(int theDivisor) : divisor(theDivisor) {
	dSize = 0;
	table = new sortedChain<K, E>[divisor];
}

template<class K,class E>
std::pair<const K, E>* hashChains<K, E>::find(const K& theKey) const {
	return table[hash(theKey) % divisor].find(theKey);
}

template<class K,class E>
void hashChains<K, E>::insert(const std::pair<const K, E>& thePair) {
	int homeBucket = static_cast<int>(hash(thePair.first) % divisor);
	int homeSize = table[homeBucket].size();
	// If thePair.fist exisits in the bucket, rewrite will happen.
	table[homeBucket].insert(thePair);
	if (table[homeBucket].size() > homeSize) {
		dSize++;

	}
}

template<class K,class E>
void hashChains<K, E>::erase(const K& theKey) {
	table[hash(theKey) % divisor]->erase(theKey);
}
