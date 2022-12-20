/**********
* queue.h
* 
* The base class for queue.
*/

#pragma once

template<class T>
class queue
{
public:
	virtual ~queue() {};
	// Return true when the queue is empty.
	virtual bool empty() const = 0;
	// Return the number of elements in the queue.
	virtual int size() const = 0;
	// Return the reference of the first element.
	virtual T& front() = 0;
	// Return the reference of the last element.
	virtual T& back() = 0;
	// Delete the first element.
	virtual void pop() = 0;
	// Add theElement to the tail(the last).
	virtual void push(const T& theElement) = 0;
};