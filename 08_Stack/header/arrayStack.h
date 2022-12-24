#pragma once
#include "stack.h"
#include <iostream>
#include <sstream>
#include "myExceptions.h"

template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
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
class arrayStack :
    public stack<T>
{
public:
    arrayStack(int initialCapacity = 10);
    ~arrayStack() { delete[] stack; }
    bool empty() const { return stackTop == -1; }
    int size() const { return stackTop + 1; }
    T& top();
    void pop();
    void push(const T&);
private:
    int stackTop; // stackTop is the index of the last element in the array, initialized by "-1".
    int arrayLength;
    T* stack; // stack is a T type pointer points to a T type array.
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    // Create the array.
    stack = new T[arrayLength];
    // Initialize.
    stackTop = -1;
}

template<class T>
T& arrayStack<T>::top()
{
    if (stackTop == -1) {
        throw stackEmpty();
    }
    return stack[stackTop];
}

template<class T>
void arrayStack<T>::pop()
{
    if (stackTop == -1) {
        throw stackEmpty();
    }
    stack[stackTop--].~T();
}

template<class T>
void arrayStack<T>::push(const T& theElement)
{
    if (stackTop == arrayLength - 1) {
        // The space is full, double the capacity.
        changeLength1D(stack, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // Push to the top of the stack (the tail of the array)
    stack[++stackTop] = theElement;
}
