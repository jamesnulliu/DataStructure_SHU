#pragma once
#include <iostream>
template<class K>
class LinearList {
public:
	virtual ~LinearList() {};
	// return true when the list is null
	virtual bool empty() const = 0;
	// return the number of elements in the line
	virtual int size() const = 0;
	// return the element whose index is "theIndex"
	virtual K& get(int theIndex) const = 0;
	// return the index of the first element whose value is "theElement"
	virtual int indexOf(const K& theElement) const = 0;
	// erase the element whose index is "theIndex"
	virtual void erase(int theIndex) = 0;
	// insert "theElement" in the location whose index is "theIndex"
	virtual void insert(int theIndex, const K& theElement) = 0;
	// insert the linear list to ostream out
	virtual void output(std::ostream& out) const = 0;
};
