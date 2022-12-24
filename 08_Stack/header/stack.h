#pragma once
template<class T>
class stack
{
public:
	virtual ~stack() {}
	virtual bool empty() const = 0; // Return ture when the stack is empty.
	virtual int size() const = 0; // Return the number of elements in the stack.
	virtual T& top() = 0; // Return the reference of the top element.
	virtual void pop() = 0; // Delete the top element.
	virtual void push(const T& theElement) = 0; // Add one element to the top of the stack.
};
