#pragma once

#include <iterator>

template<class T>
class iterator {
public:
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;
	// constructor
	iterator(T* thePostion = nullptr) :position(thePostion) {}

	// dereference operator
	T& operator*() const { return *position; }
	T* operator->() const { return &*position; }
	// addition
	iterator& operator++() {
		++position;
		return *this;
	}
	iterator operator++(int) {
		iterator old = *this;
		++position;
		return old;
	}
	// subtraction
	iterator& operator--() {
		--position;
		return *this;
	}
	iterator operator--(int) {
		iterator old = *this;
		--position;
		return old;
	}
	// equal
	bool operator!=(const iterator right) const {
		return position != right.position;
	}
	bool operator==(const iterator right) const {
		return position == right.position;
	}
private:
	T* position;
};