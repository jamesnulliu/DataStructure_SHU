// linked implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// unidirectional iterator for dChain included

#ifndef dChain_
#define dChain_

#include <iostream>
#include <sstream>
#include <string>
#include "linearList.h"
#include "myExceptions.h"

template<class T>
struct dChainNode
{
    T element;
    dChainNode<T>* prev;
    dChainNode<T>* next;

    // Constructor:
    dChainNode(const T& e = {}, dChainNode<T>* p = nullptr, dChainNode<T>* n = nullptr) :element(e), prev(p), next(n) {}
};

template<class T>
using node = dChainNode<T>;

template<class T>
class dChain : public linearList<T>
{
    // Simplize code:
    template<class TT> using node = dChainNode<TT>;
public:
    // constructor, copy constructor and destructor
    dChain(int initialCapacity = 10);
    dChain(const dChain<T>&);
    ~dChain();

    // iterators to start and end of list
    class iterator;
    iterator begin() { return iterator(firstNode); }
    iterator end() { return iterator(nullptr); }

    // ADT methods
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T& get(int theIndex) const;
    // Return index of first occurrence of {theElement}, -1 if {theElement} not in list.
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    // Using iterator could be faster than using index.
    void insert(iterator it, const T& theElement);
    void output(std::ostream& out) const;

    // iterator for class {dChain}:
    class iterator
    {
    public:
        // Typedefs required by C++ for a bidirectional iterator:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        // Constructor:
        iterator(node<T>* theNode = nullptr) { nodePTR = theNode; }

        // Dereferencing operators:
        T& operator*() const { return nodePTR->element; }
        T* operator->() const { return &nodePTR->element; }

        // Increment:
        iterator& operator++() { nodePTR = nodePTR->next; return *this; }
        iterator operator++(int) { iterator old = *this; nodePTR = nodePTR->next; return old; }
        iterator operator+(ptrdiff_t offset) const
        {
            node<T>* theNode = this->nodePTR;
            for (int i = 0; i < offset; ++i) {
                theNode = theNode->next;
            }
            return theNode;
        }

        // Decrement:
        iterator& operator--() { nodePTR = nodePTR->prev; return *this; }
        iterator operator--(int) { iterator old = *this; nodePTR = nodePTR->prev; return old; }
        iterator operator-(ptrdiff_t offset) const
        {
            // Following code is problematic.
            // Not all nullptr implies {end()}, while chain without tailnode can not solve the problem easily.
            // @{
            node<T>* theNode = this->nodePTR;
            if (theNode == nullptr) {
                theNode = nullptr;
                --offset;
            }
            // @}
            for (int i = 0; i < offset; ++i) {
                theNode = theNode->prev;
            }
            return theNode;
        }

        // Equality testing:
        bool operator!=(const iterator& right) const { return nodePTR != right.nodePTR; }
        bool operator==(const iterator& right) const { return nodePTR == right.nodePTR; }
        node<T>* nodePTR;
    };  // end of iterator class

protected:
    void checkIndex(int theIndex) const;

    node<T>* firstNode;  // pointer to first node in dChain
    node<T>* lastNode;   // pointer to last node in dChain
    int listSize;        // number of elements in list
};

template<class T>
dChain<T>::dChain(int initialCapacity)
{
    firstNode = lastNode = nullptr;
    listSize = 0;
}

template<class T>
dChain<T>::dChain(const dChain<T>& theList)
{
    listSize = theList.listSize;
    if (listSize == 0) { firstNode = nullptr; return; }

    node<T>* sourceNode = theList.firstNode;
    firstNode = new node<T>(sourceNode->element);
    // copy first element of theList
    sourceNode = sourceNode->next;
    node<T>* targetNode = firstNode;
    // current last node in *this
    while (sourceNode != NULL)
    {// copy remaining elements
        targetNode->next = new node<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL; // end the dChain
}

template<class T>
dChain<T>::~dChain()
{// Chain destructor. Delete all nodes in dChain.
    node<T>* nextNode;
    while (firstNode != nullptr)
    {// delete firstNode
        nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class T>
void dChain<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template<class T>
T& dChain<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    node<T>* currentNode = firstNode;
    for (int i = 0; i < theIndex; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->element;
}

template<class T>
int dChain<T>::indexOf(const T& theElement) const
{
    // search the dChain for theElement
    node<T>* currentNode = firstNode;
    int index = 0;  // index of currentNode
    while (currentNode != nullptr && currentNode->element != theElement) {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == nullptr) return -1;
    else return index;
}

template<class T>
void dChain<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    node<T>* deleteNode; // {deleteNote} should point to the node to be deleted
    if (theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
        firstNode->prev = nullptr;
    } else if (theIndex == listSize - 1) {
        deleteNode = lastNode;
        lastNode = deleteNode->prev;
        lastNode->next = nullptr;
    } else {
        // Get the predecessor of desired node:
        node<T>* pre = firstNode;
        for (int i = 0; i < theIndex - 1; i++) { pre = pre->next; }
        deleteNode = pre->next;
        pre->next = pre->next->next;
        pre->next->prev = pre;
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void dChain<T>::insert(int theIndex, const T& theElement)
{
    // Insert theElement so that its index is {theIndex}.
    // Handle invaid index:
    if (theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    if (listSize == 0) {
        firstNode = lastNode = new node<T>(theElement);
        ++listSize;
        return;
    }
    if (theIndex == 0) {
        // Insert at front:
        firstNode = new node<T>(theElement, nullptr, firstNode);
        firstNode->next->prev = firstNode;
    } else if (theIndex == listSize) {
        // Insert at back:
        lastNode = new node<T>(theElement, lastNode, nullptr);
        lastNode->prev->next = lastNode;
    } else {
        // Find predecessor of new element
        node<T>* pre = firstNode;
        for (int i = 0; i < theIndex - 1; i++) pre = pre->next;
        // Insert after pre:
        pre->next = new node<T>(theElement, pre, pre->next);
        pre->next->prev = pre->next;
    }
    listSize++;
}

template<class T>
void dChain<T>::insert(iterator it, const T& theElement)
{
    if (it == begin()) {
        insert(0, theElement);
    } else if (it == end()) {
        insert(listSize, theElement);
    } else {
        node<T>* tNode = new node<T>(theElement, (it - 1).nodePTR, (it + 1).nodePTR);
    }
}

template<class T>
void dChain<T>::output(std::ostream& out) const
{// Put the list into the stream out.
    for (node<T>* currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->next) {
        out << currentNode->element << "  ";
    }
}

// Overload <<:
template <class T>
std::ostream& operator<<(std::ostream& out, const dChain<T>& x) { x.output(out); return out; }

#endif
