#pragma once

#include <iterator>

template<class K, class E>
class iterator {
public:
	typedef std::pair<K, E> itType;
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef itType value_type;
	typedef ptrdiff_t difference_type;
	typedef itType* pointer;
	typedef itType& reference;
	// constructor
	iterator(itType* thePostion = nullptr) :position(thePostion) {}

	// dereference operator
	itType& operator*() const { return *position; }
	itType* operator->() const { return &*position; }
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
	itType* position;
};