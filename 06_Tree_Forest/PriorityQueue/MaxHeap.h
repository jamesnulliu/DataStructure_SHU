#pragma once

#include "PriorityQueue.h"
#include "myExceptions.h"

#ifndef DEFAULT_CAPACITY
#define DEFAULT_CAPACITY 100
#endif // !DEFAULT_CAPACITY

template<class T>
class maxHeap :
    public priorityQueue<T>
{
public:

    maxHeap(int c = DEFAULT_CAPACITY) :capacity(c)
    {
        heap = new T[capacity];
        heapSize = 0;
    }
    maxHeap(const maxHeap& theHeap);
    ~maxHeap()
    {
        delete[] heap;
    }
    bool empty() const { return heapSize == 0; }
    int size() const { return heapSize; }
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
    void deactivateArray()
    {
        heap = nullptr;
    }
public:
    const T& top() { return *heap; }
    // Delete the largest element in the tree.
    void pop();
    // Push 'theElement' to the tree.
    void push(const T& theElement);
    // Remove and return "heap[i]"
    T remove(int i);
    void initialize(T* theHeap, int theSize);
    void outputArray() const;
private:
    int heapSize;
    T* heap;
    int capacity;
};

template<class T>
maxHeap<T>::maxHeap(const maxHeap<T>& theHeap)
{
    heap = new T[theHeap.heapSize + 1];
    heapSize = theHeap.heapSize;
    capacity = heapSize + 1;
    for (int i = 1; i <= heapSize; i++) {
        heap[i](theHeap.heap[i]);
    }
}

template<class T>
void maxHeap<T>::push(const T& theElement)
{
    // Increase the capacity of the array if necessary.
    if (heapSize == capacity - 1) {
        changeLength1D(heap, capacity, 2 * capacity);
        capacity *= 2;
    }
    // Find the location for "theElement" to insert in.
    int currentNode = ++heapSize; // move "current" to root, starting from new node(the additional).
    while (currentNode != 1 && heap[currentNode / 2] < theElement) {
        // In a complete binary tree, a child's father node is theNode / 2.
        heap[currentNode] = heap[currentNode / 2];
        currentNode /= 2;
    }
    heap[currentNode] = theElement;
}

template<class T>
void maxHeap<T>::pop()
{
    if (heapSize == 0) throw queueEmpty();
    // Delete the largest element.
    heap[1].~T();
    // Delete the last element and re-construct the heap.
    T lastElement = heap[heapSize];
    heap[heapSize--].~T();
    // Starting from the root, find location for the last element.
    int current = 1,
        child = 2;
    // Loop until the end.
    while (child <= heapSize) {
        // "child" should be the larger child of "current"
        if (child < heapSize && heap[child] < heap[child + 1]) { child++; }
        // IF: "current" points to a node whose child is smaller than "lastElement",
        // indicating that "lastElement" can be put in "heap[current]".
        if (lastElement >= heap[child]) {
            // End loop.
            break;
        }
        // OTHERWISE.
        else {
            heap[current] = heap[child];
            current = child;
            // Move "child" to its child.
            child <<= 1;
        }
    }
    heap[current] = lastElement;
}

template<class T>
T maxHeap<T>::remove(int i)
{
    if (heapSize == 0) throw queueEmpty;
    T theDeleted = heap[i];
    T lastElement = heap[heapSize];
    heap[heapSize].~T();
    int current = i, child = i << 1;
    while (child <= heapSize) {
        // Make sure "child" points to the larger one between the sublings.
        if (child < heapSize && heap[child] < heap[child + 1]) {
            child++;
        }
        // IF: "current" points to a node whose child is smaller than "lastElement",
        // indicating that "lastElement" can be put in "heap[current]".
        if (lastElement >= heap[child]) {
            // End loop.
            break;
        }
        // OTHERWISE.
        else {
            heap[current] = heap[child];
            current = child;
            child << 1;
        }
    }
    heap[current] = lastElement;
    return theDeleted;
}

template<class T>
void maxHeap<T>::initialize(T* theHeap, int theSize)
{
    delete[] heap; // Empty the memory of "T* maxHeap<T>::heap".
    heap = theHeap; // Make "heap" points to "theHeap".
    heapSize = theSize; // Set the "heapSize".

    // 'root' would iterates from {heapSize/2 (parent of the last element)} and keep decreasing until reaches real root.
    for (int root = heapSize / 2; root >= 1; root--) {
        // Pick up the current element of 'root'.
        T rootElement = heap[root];
        int child = 2 * root;
        // 'child' iterates from the child of current root to end, but cannot be larger than 'heapSize'.
        for (; child <= heapSize; child *= 2) {
            // Ensure 'heap[child]' is the larger one between the siblings.
            if (child < heapSize && heap[child] < heap[child + 1]) { child++; }
            if (rootElement >= heap[child]) { // IF: 'rootElement' can be put in 'heap[child/2]'.
                break;
            }
            // IF: "rootElement" cannot be put in "heap[child/2]".
            // Move 'heap[child]' to 'heap[child/2]'.
            heap[child / 2] = heap[child];
            // Re-allocate the next level to 'child'.
        }
        heap[child / 2] = rootElement;
    }
}

template<class T>
void maxHeap<T>::outputArray() const
{
    std::cout << "Output in array form: ";
    for (int i = 1; i <= heapSize; i++) {
        std::cout << heap[i] << ' ';
    }
    std::cout << std::endl;
}
