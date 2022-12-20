#pragma once
#include "Dictionary.h"

template <class K, class E>
struct pairNode
{
	std::pair<const K, E> element;
	pairNode<K, E>* next;
	pairNode() {}
	pairNode(const std::pair<const K,E>& thePair) :element(thePair) {}
	pairNode(const std::pair<const K, E>& thePair, pairNode<K, E>* p) :element(thePair), next(p) {}
};

template <class K, class E>
class sortedChain :
	public dictionary<K, E>
{
public:
	sortedChain();
	sortedChain(const std::pair<const K, E>& thePair);
	~sortedChain();
public:
	std::pair<const K, E>* find(const K& theKey) const;
	void insert(const std::pair<const K, E>& thePair);
	void erase(const K& theKey);
	int size() const { return dSize; }
	bool empty() const { return dSize == 0; }
protected:
	pairNode<K, E>* firstNode;
	int dSize;
};

template<class K,class E>
sortedChain<K, E>::sortedChain() {
	firstNode = nullptr;
	dSize = 0;
}

template<class K, class E>
sortedChain<K, E>::sortedChain(const std::pair<const K, E>& thePair) {
	firstNode = nullptr;
	dSize = 0;
	insert(thePair);
}

template<class K,class E>
sortedChain<K, E>::~sortedChain() {
	if (firstNode == nullptr) return;
	pairNode<K, E>* p = firstNode->next;
	while (true) {
		delete firstNode;
		if (p == nullptr) return;
		firstNode = p;
		p = p->next;
	}
	
}

template <class K,class E>
std::pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const {
	pairNode<K, E>* currentNode = firstNode;
	// Loop until the end or theKey is found.
	while (currentNode != nullptr && currentNode->element.first != theKey) {
		currentNode = currentNode->next;
	}
	// IF: theKey is found.
	if (currentNode != nullptr && currentNode->element.first == theKey) {
		return &currentNode->element;
	}
	// theKey is not found.
	return nullptr;
}


template <class K, class E>
void sortedChain<K, E>::insert(const std::pair<const K, E>& thePair) {
	pairNode<K, E>* p = firstNode, * tp = nullptr;
	while (p != nullptr && p->element.first < thePair.first) {
		tp = p;
		p = p->next;
	}
	// IF: there is matched pair
	if (p != nullptr && p->element.first == thePair.first) {
		// Substitute for old.
		p->element.second = thePair.second;
		return;
	}
	// IF: there is no matched pair, establish a new node with thePair.
	pairNode<K, E>* newNode = new pairNode<K, E>(thePair, p);
	// Insert new node after tp.
	if (tp == nullptr) {
		firstNode = newNode;
	}
	else {
		tp->next = newNode;
	}
	dSize++;
	return;
}

template<class K,class E>
void sortedChain<K, E>::erase(const K& theKey) {
	pairNode<K, E>* p = firstNode, * tp = nullptr; // tp trails p
	// Search for the pair with theKey.
	// Loop until the end or theKey is found.
	while (p != nullptr && p->element.first < theKey) {
		tp = p;
		p = p->next;
	}
	// Confine whether matched.
	// IF: matched.
	if (p != nullptr && p->element.first == theKey) {
		// Delete p from the chain.
		if (tp == nullptr) {
			firstNode = p->next;
		}
		else {
			tp->next = p->next;
		}
		delete p;
		dSize--;
	}
}
