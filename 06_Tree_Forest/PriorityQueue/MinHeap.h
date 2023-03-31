#pragma once

#include <iostream>
#include "PriorityQueue.h"
#include "myExceptions.h"
#include "myExceptions.h"

#ifndef DEFAULT_CAPACITY
#define DEFAULT_CAPACITY 100
#endif // !DEFAULT_CAPACITY

template<class T>
class minHeap :
    public priorityQueue<T>
{
public:
    minHeap(int c = DEFAULT_CAPACITY) :capacity(c) {
        heap = new T[capacity];
    }
    ~minHeap() {
        delete[] heap;
    }
    bool empty() const { return heapSize == 0; }
    int size() const { return heapSize; }
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

public:
    const T& top() { return *heap; }
    // Delete the largest element in the tree.
    void pop();
    // Push "theElement" to the tree.
    void push(const T& theElement);
    void initialize(T* theHeap, int theSize);

    void outputArray() const;
private:
    int heapSize;
    T* heap;
    int capacity;
};

template<class T>
void minHeap<T>::push(const T& theElement) {
    // Increase the capacity of the array if necessary.
    if (heapSize == capacity - 1) {
        changeLength1D(heap, capacity, 2 * capacity);
        capacity *= 2;
    }
    // Find the location for "theElement" to insert in.
    int currentNode = ++heapSize; // move "currentNode" to root, starting from new node(the additional).
    while (currentNode != 1 && heap[currentNode / 2] > theElement) {
        // In a complete binary tree, a child's father node is theNode / 2.
        heap[currentNode] = heap[currentNode / 2];
        currentNode /= 2;
    }
    heap[currentNode] = theElement;
}

template<class T>
void minHeap<T>::pop() {
    if (heapSize == 0) throw queueEmpty();
    // Delete the largest element.
    heap[1].~T();
    // Delete the last element and re-construct the heap.
    T lastElement = heap[heapSize--];
    // Starting from the root, find location for the last element.
    int currentNode = 1,
        child = 2;
    // Loop until the end.
    while (child <= heapSize) {
        // "child" should be the larger child of "currentNode"
        if (child < heapSize && heap[child] < heap[child + 1]) { child++; }
        // IF: "lastElement" can be put in "heap[currentNode]".
        if (lastElement >= heap[child]) { break; }
        // IF: "lastElement" cannot be put in "heap[currentNode]".
        // Move child upward(remenber: "root" is empty at first").
        heap[currentNode] = heap[child];
        // Iterate "currentNode".
        currentNode = child;
        // Move "child" to its left node, but can't make sure it's the larger node.
        child *= 2;
    }
    heap[currentNode] = lastElement;
}

template<class T>
void minHeap<T>::initialize(T* theHeap, int theSize) {
    delete[] heap;
    // Root.
    heap = theHeap;
    heapSize = theSize;
    if (heapSize > capacity) {
        changeLength1D(heap, capacity, capacity = heapSize);
    }
    // 'root' would iterates from 'heapSize' / 2 and keep decreasing until reaches real root.
    for (int _root = heapSize / 2; _root >= 1; _root--) {
        // Pick up the current element of 'root'.
        T rootElement = heap[_root];
        int child = 2 * _root;
        // 'child' iterates from the child of current root, but cannot be larger than 'heapSize'.
        for (; child < heapSize; child *= 2) {
            // Ensure 'heap[child]' the larger one among the brothers.
            if (child < heapSize && heap[child] < heap[child + 1]) {
                child++;
            }
            // IF: 'rootElement' can be put in 'heap[child/2]'.
            if (rootElement >= heap[child]) {
                break;
            }
            // IF: "rootElement" cannot be put in "heap[child/2]".
            // Move 'heap[child]' to 'heap[root]'.
            heap[_root] = heap[child];
            // Re-allocate the next level to 'child'.
            child *= 2;
        }
        heap[child / 2] = rootElement;
    }
}

template<class T>
void minHeap<T>::outputArray() const {
    std::cout << "Output in array form: ";
    for (int i = 1; i <= heapSize; i++) {
        std::cout << heap[i] << ' ';
    }
    std::cout << std::endl;
}