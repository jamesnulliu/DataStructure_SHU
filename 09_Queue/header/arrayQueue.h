/**********
* In array queue, we need to be aware of the location formula:
* $$ location(i) = (location(thefront) + 1 ) % arrayLength $$
*
* Another thing worth noting is that,
* in our implementation,
* {queueFront} is the index of the elem AHEAD OF the first;
* while {queueBack} is the index of just the last elem.
* This is slightly different from <arrayList>.
*/

#pragma once

#include "queue.h"
#include <sstream>
#include "myExceptions.h"

template<class T>
class arrayQueue : public queue<T>
{
public:
    arrayQueue(int initialCapacity = 10);
    ~arrayQueue() { delete[] queue; }
    bool empty() const
    {
#ifdef use_length
        return !queueLength;
#else
        return queueBack == queueFront;
#endif // !use_length
    }
    // Return the number of elements in the queue.
    int size() const
    {
#ifdef use_length
        return queueLength;
#else
        return (capacity + queueBack - queueFront) % capacity;
#endif
    }
    // Add theElement to the queueBack.
    void push(const T& theElement);
    // Delete the first element.
    void pop();
    T& front() { return queue[(queueFront + 1) % capacity]; }
    T& back()
    {
        return queue[queueBack];
    }

private:
    T* queue;
    int capacity;
    int queueFront;   // index of the elem AHEAD OF the first
    int queueBack;    // index of the last elem
    int queueLength;
};

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0.";
        throw illegalParameterValue(s.str());
    }
    capacity = initialCapacity;
    // Create the queue.
    queue = new T[capacity];
    // Initialize.
    queueFront = queueBack = 0;
    queueLength = 0;
}

template<class T>
void arrayQueue<T>::push(const T& theElement)
{
    // If full, increase the length of the array.
    if (this->size() + 1 == capacity) {
        T* newQueue = new T[2 * capacity];
        // {start} indicates whether {queueBack} has surpassed {capacity - 1}.
        int start = (queueFront + 1) % capacity;
        // Copy the old queue to the new.
        // If {queueBack} not supasses index {0}:
        if (start < 2) {
            std::copy(queue + start, queue + start + capacity - 1, newQueue);
        }
        // If {queueBack} surpasses index {0}, then we neet to copy twice:
        else {
            std::copy(queue + start, queue + capacity, newQueue);
            std::copy(queue, queue + queueBack + 1, newQueue + capacity - start);
        }
        queueFront = 2 * capacity - 1;
        queueBack = capacity - 2;
        capacity *= 2;
        delete[] queue;
        queue = newQueue;
    }
    // Add theElement the queueBack.
    queueBack = (queueBack + 1) % capacity;
    queue[queueBack] = theElement;
    queueLength += 1;
}

template<class T>
void arrayQueue<T>::pop()
{
    // IF: the queue is empty.
    if (this->empty()) { throw queueEmpty(); }
    queueFront = (queueFront + 1) % capacity;
    queue[queueFront].~T();
    queueLength -= 1;
}
