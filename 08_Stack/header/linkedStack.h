#pragma once
/*
* We use the left side of the list to be the top of the stack.
*/

#include "stack.h"
#include "Chain.h"
#include "myExceptions.h"
template<class T>
class linkedStack :
    public stack<T>
{
public:
    linkedStack(int initialCapacity = 10) { stackTop = nullptr; stackSize = 0; }
    ~linkedStack();
    bool empty() const { return !stackSize; }
    int size() const { return stackSize; }
    T& top();
    void pop();
    void push(const T&);
    void popNode(ChainNode<T>*);
    void pushNode(ChainNode<T>*);
private:
    ChainNode<T>* stackTop;	// The pointer to the top element;
    int stackSize; // The number of elements in the stack.
};

template<class T>
linkedStack<T>::~linkedStack()
{
    while (stackTop != nullptr) {
        ChainNode<T>* nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
    }
}

template<class T>
T& linkedStack<T>::top()
{
    if (!stackSize) {
        throw stackEmpty();
    }
    return stackTop->element;
}

template<class T>
void linkedStack<T>::pop()
{
    if (!stackSize) {
        throw stackEmpty();
    }
    ChainNode<T>* nextNode = stackTop->next;
    delete stackTop;
    stackTop = nextNode;
    stackSize--;
}

template<class T>
void linkedStack<T>::push(const T& theElement)
{
    stackTop = new ChainNode<T>(theElement, stackTop);
    stackSize++;
}

template<class T>
void linkedStack<T>::popNode(ChainNode<T>* theNode)
{
    if (stackTop != theNode) {
        return;
    }
    pop();
}

template<class T>
void linkedStack<T>::pushNode(ChainNode<T>* theNode)
{
    theNode->next = stackTop;
    stackTop = theNode;
    stackSize++;
}
