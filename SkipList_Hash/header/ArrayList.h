#pragma once
#include <iostream>
#include <sstream>
#include "LinearList.h"
#include "Iterator.h"
#include "myexception.h"

template<class T>
class SortedArrayList :
	public LinearList<T>
{
public:
	// constructor
	SortedArrayList(int initialCapacity = 10);
	// copy constructor
	SortedArrayList(const SortedArrayList<T>&);
	// destructor
	~SortedArrayList() { delete [] element; }

	// ADT(abstract data type) method
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;

	// other method
	int capacity() const { return arrayLength; }

public:
	/*
	* To create an iterator: 
	* arrayList<int>::iterator x = y.begin();
	*/
	iterator<T> begin() {
		return iterator<T>(element);
	}
	iterator<T> end() {
		return iterator<T>(element + listSize);
	}
protected:
	// throw out error when "theIndex" is invalid
	void checkIndex(int theIndex) const;
	T* element;
	int arrayLength;
	int listSize;
};

template<class T>
void changeLength1D(T*& a, int oldLength, int newLength) {
	if (newLength < 0) {
		throw illegalParameterValue("new length must be >= 0");
	}
	T* temp = new T[newLength];
	int number = std::min(oldLength, newLength);
	std::copy(a, a + number, temp);
	delete[] a;
	a = temp;
}

template<class T>
void changeLength2D(T**& a, int row, int oldCol, int newCol) {
	if (newCol < 0) {
		throw illegalParameterValue("new length must be >= 0");
	}
	T* temp = new T[row][newCol];
	int number = std::min(oldCol, newCol);
	for (int i = 0; i < row; i++) {
		std::copy(a[i], a[i] + number, temp[i]);
		delete[] a[i];
		a[i] = temp[i];
	}
}

template<class T>
SortedArrayList<T>::SortedArrayList(int initialCapacity) {
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template<class T>
SortedArrayList<T>::SortedArrayList(const SortedArrayList<T>& theList) {
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
}

template<class T>
void SortedArrayList<T>::checkIndex(int theIndex) const {
	if (theIndex < 0 || theIndex >= listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<class T>
T& SortedArrayList<T>::get(int theIndex) const {
	checkIndex(theIndex);
	return element[theIndex];
}


template<class T>
int SortedArrayList<T>::indexOf(const T& theElement) const {
	int theIndex = (int)(std::find(element, element + listSize, theElement) - element);
	if (theIndex == listSize) {
		return -1;
	}
	else {
		return theIndex;
	}
}

template<class T>
void SortedArrayList<T>::erase(int theIndex) {
	checkIndex(theIndex);
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);
	element[--listSize].~T();
}

template<class T>
void SortedArrayList<T>::insert(int theIndex, const T& theElement) {
	if (theIndex<0 || theIndex>listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	// if the array is full, double the capacity
	if (listSize == arrayLength) {
		changeLength1D<T>(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	// move the elements to the right, starting from
	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);

	element[theIndex] = theElement;
	listSize++;
}

template<class T>
void SortedArrayList<T>::output(std::ostream& out) const {
	std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, " "));
}

template<class T>
std::ostream& operator<<(std::ostream& out, const SortedArrayList<T>& x) {
	x.output(out);
	return out;
}


