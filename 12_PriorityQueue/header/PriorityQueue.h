#pragma once
template<class T>
class priorityQueue
{
public:
	virtual ~priorityQueue() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual const T& top() = 0;
	virtual void pop() = 0;
	virtual void push(const T& theElement) = 0;
};
