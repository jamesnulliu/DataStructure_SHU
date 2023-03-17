#pragma once
#include "Dictionary.h"
#include <sstream>
#include "myexception.h"

template<class K, class E>
void changeLength1D(std::pair<K,E>* a, int oldLength, int newLength) {
	if (newLength < 0) {
		throw illegalParameterValue("new length must be >= 0");
	}
	std::pair<K,E>* temp = new std::pair<K, E>[newLength];
	int number = std::min(oldLength, newLength);
	std::copy(a, a + number, temp);
	delete[] a;
	a = temp;
}

template<class K, class E>
class sortedArrayList
	// : public dictionary<K, E>
{
public:
	sortedArrayList(int initialCapacity = 10);
	~sortedArrayList() { delete[] element; }
public:
	std::pair<K, E>* find(const K& theKey) const;
	void insert(const std::pair<const K, E>& thePair);
	void erase(const K& theKey);
	int size() const { return dSize; }
	bool empty() const { return dSize == 0; }
protected:
	std::pair<K, E>* element;
	int capacity;
	int dSize;
};

template<class K, class E>
sortedArrayList<K, E>::sortedArrayList(int initialCapacity) {
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	capacity = initialCapacity;
	element = new std::pair<K,E>[capacity];
	dSize = 0;
}

template<class K, class E>
std::pair<K,E>* sortedArrayList<K, E>::find(const K& theKey)const {
	if (empty()) {
		return nullptr;
	}
	int left = 0, right = dSize - 1, mid;

	while (left <= right) {
		mid = (left + right) / 2;
		if (element[mid].first < theKey) {
			left = mid + 1;
		}
		else if (element[mid].first > theKey) {
			right = mid - 1;
		}
		else {
			return element + mid;
		}
	}
	return nullptr;
}

template<class K,class E>
void sortedArrayList<K, E>::insert(const std::pair<const K, E>& thePair) {
	if (empty()) {
		element[0] = thePair;
		dSize++;
		return;
	}
	// IF: the array is full, double the capacity.
	if (dSize == capacity) {
		changeLength1D<K,E>(element, capacity, 2 * capacity);
		capacity *= 2;
	}

	int left = 0, right = dSize - 1, mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (element[mid].first < thePair.first) {
			if (left == right) {
				std::copy_backward(element + mid + 1, element + dSize, element + dSize + 1);
				element[mid+1] = thePair;
				dSize++;
				return;
			}
			left = mid + 1;
		}
		else if (element[mid].first > thePair.first) {
			if (left == right) {
				std::copy_backward(element + mid, element + dSize, element + dSize + 1);
				element[mid] = thePair;
				dSize++;
				return;
			}
			right = mid - 1;
		}
		else {
			element[mid].second = thePair.second;
			dSize++;
			return;
		}
	}
	// Error.
	printf("error\n");
	return;
}

template<class K, class E>
void sortedArrayList<K, E>::erase(const K& theKey) {
	std::pair<K,E>* theElement = find(theKey);
	if (theElement == nullptr) {
		printf("Not found.\n");
		return;
	}
	std::copy(theElement + 1, element + dSize, theElement);
	delete (element + dSize - 1);
	return;
}