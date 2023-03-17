#pragma once
#include "Dictionary.h"
#include <cmath>
#include <sstream>
#include "myexception.h"
#include "DIterator.h"

// The probability of a dictionaty belongs to the ith list as well as (i-1)th list.
// "probe" should be more than 0 and less than 1.
constexpr auto probe = 0.5;

template<class K, class E>
struct skipNode
{
	typedef std::pair<const K, E> pairType;
	pairType element;
	skipNode<K, E>** next; // An array of pointers.
	skipNode(const pairType& thePair, int size) :element(thePair) {
		next = new skipNode<K, E>*[size];
	}
};

template<class K, class E>
class skipList :
	public sortedChain<K, E>
{
public:
	/**
	* @breif	Constructor of class "skipList".
	*
	* @see		skipList::tailKey
	* @param	largeKey	The value will be stored in "tailKey", limiting the generated keys.
	* @param	maxPairs	"dSize" will always be less than "maxPairs".
	* @param	prob		0 < prob < 1. The probability of a dictionaty belongs to the ith list as well as (i-1)th list
	*/
	skipList(K largeKey, int maxPairs, float prob);
	/**
	* @brief	Return matched pair's pointer
	*
	* @param	theKey	The key to find.
	*/
	std::pair<const K, E>* find(const K& theKey) const;
	/**
	* @brief	The method to allocate level.
	*
	* @see		skipList::maxLevel
	* @return	a random integer which must not be bigger than "maxLevel", indicating the level of the list
	*/
	int level() const;
	/**
	* @brief	Search for "theKey" and store the last node's pointer of every list level in "last".
	*
	* @see		skiplist::last
	* @param	theKey	The Key to search for.
	* @return	pointer of the node whose key is "theKey"
	*/
	skipNode<K, E>* search(const K& theKey) const;
	/**
	* @brief	Insert "thePair" to dictionary, cover the pair with the same key.
	*
	* @param	thePair	The pair to be inserted.
	*/
	void insert(const std::pair<const K, E>& thePair);
	/**
	* @brief	Delete a pair whose key is "theKey" from skip list.
	*
	* @param	theKey	The key to search for.
	*/
	void erase(const K& theKey);
public:
	/*
	* To create an iterator:
	* skipList<K,E>::iterator x = y.begin();
	*/
	iterator<K, E> begin() {
		return iterator<K, E>(headNode + 1);
	}
	iterator<K, E> end() {
		return iterat
			or<K, E>(tailNode);
	}
protected:
	float cutOff; // To confine the number of levels.
	int levels; // The largest non-empty list.
	int dSize; // The number of stored dictionary.
	int maxLevel; // Allowed largest number of levels.
	K tailKey; // The largest key.
	pairNode<K, E>* headNode;
	pairNode<K, E>* tailNode;
	skipNode<K, E>** last; // last[i] infers the last node of the ith level.
};

template<class K, class E>
skipList<K, E>::skipList(K largeKet, int maxPairs, float prob) {
	cutOff = prob * RAND_MAX;
	maxLevel = static_cast<int>(ceil(logf(static_cast<float>(maxPairs) / logf(1 / prob)))) - 1;
	levels = 0; // Initialize levels.
	dSize = 0;
	tailKey = largeKet;

	// Generate following staff.
	std::pair<K, E> tailPair;
	tailPair.first = tailKey;
	headNode = new skipNode<K, E>(tailPair, maxLevel + 1);
	tailNode = new skipNode<K, E>(tailPair, 0);
	last = new skipNode<K, E>*[maxLevel + 1];

	// When the list is empty, the headNode of any level points to tailNode.
	for (int i = 0; i <= maxLevel; i++) {
		headNode->next[i] = tailNode;
	}
}

template<class K, class E>
std::pair<const K, E>* skipList<K, E>::find(const K& theKey)const {
	// IF: theKey is lager than the lagest key.
	if (theKey >= tailKey) {
		return nullptr;
	}
	// The position of beforeNode is the most right position before the node whose key is theKey.
	skipNode<K, E>* beforeNode = headNode;
	// Loop from the superior lists to junior lists.
	for (int i = levels; i >= 0; i--) {
		// Track the pointer of the ith list's point.
		while (beforeNode->next[i]->element.first < theKey) {
			beforeNode = beforeNode->next[i];
		}
	}
	// Check whether the key of next node is theKey.
	if (beforeNode->next[0]->element.first == theKey) {
		return &beforeNode->next[0]->element;
	}
	// No matched node.
	return nullptr;
}

template<class K, class E>
int skipList<K, E>::level() const {
	int lev = 0;
	while (rand() <= cutOff) {
		lev++;
	}
	return (lev <= maxLevel) ? lev : maxLevel;
}

template<class K, class E>
skipNode<K, E>* skipList<K, E>::search(const K& theKey) const {
	// The position of beforeNode is the most right position before the node whose key is theKey.
	skipNode<K, E>* beforeNode = headNode;
	for (int i = levels; i >= 0; i--) {
		while (beforeNode->next[i]->element.first < theKey) {
			beforeNode = beforeNode->next[i];
		}
		// The node on the last list level i.
		last[i] = beforeNode;
	}
	return beforeNode->next[0];
}

template<class K, class E>
void skipList<K, E>::insert(const std::pair<const K, E>& thePair) {
	// IF: the key of thePair is to large.
	if (thePair.first >= tailKey) {
		std::ostringstream s;
		s << "Key = " << thePair.first << " Must be < " << tailKey;
		throw illegalParameterValue(s.str());
	}
	// Check whether the pair whose key is "thePair" exsists.
	skipNode<K, E>* theNode = search(thePair.first);
	// IF: exist, update the value of the pair.
	if (theNode->element.first == thePair.first) {
		theNode->element.second = thePair.second;
		return;
	}
	// IF: not exist, confine the level of the new node.
	int theLevel = level();
	// Make "theLevel" <= "levels" + 1
	if (theLevel > levels) {
		theLevel = ++levels;
		last[theLevel] = headNode;
	}
	// Insert new node after "theNode".
	skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
	for (int i = 0; i <= theLevel; i++) {
		// Insert the ith level list.
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
	}
	dSize++;
	return;
}

template<class K, class E>
void skipList<K, E>::erase(const K& theKey) {
	if (theKey >= tailKey) return;
	// Check for matched pair.
	skipNode<K, E>* theNode = search(theKey);
	if (theNode->element.first != theKey) return;
	// Delete node from skip list.
	for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++) {
		last[i]->next[i] = theNode->next[i];
	}
	// Update the level of the list.
	while (levels > 0 && headNode->next[levels] == tailNode) {
		levels--;
	}
	delete theNode;
	dSize--;
}
