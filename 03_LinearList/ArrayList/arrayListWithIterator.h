// array implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// USES STL ALGORITHMS TO SIMPLIFY CODE
// iterator class for arrayList included

#ifndef arrayList_
#define arrayList_

#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include<unordered_set>
#include<iterator>
#include "linearList.h"
#include "myExceptions.h"
#include "changeLength1D.h"

using namespace std;

template<class T>
class arrayList : public linearList<T>
{
public:
    // constructor, copy constructor and destructor
    constexpr arrayList() = default;
    constexpr arrayList(const arrayList<T>&);
    constexpr arrayList(std::initializer_list<T> initList);
    constexpr ~arrayList() { delete[] element; }

    // ADT methods
    constexpr bool empty() const { return listSize == 0; }
    constexpr int size() const { return listSize; }
    constexpr T& get(int theIndex) const;
    constexpr int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;

    // additional method
    constexpr int capacity() const { return listCapacity; }
    // Shrink the list to make each element appear only once. O(n2)
    void shrink_to_unique_On2();
    // Shrink the list to make each element appear only once. O(n)
    void shrink_to_unique_On();
    void push_back(const T& tElement) { insert(listSize, tElement); }
    void reverse();

    // iterators to start and end of list
    class iterator;
    constexpr iterator begin() { return iterator(element); }
    constexpr iterator end() { return iterator(element + listSize); }

    // iterator for arrayList
    class iterator
    {
    public:
        // typedefs required by C++ for a bidirectional iterator
        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        // constructor
        constexpr iterator(T* thePosition = 0) { position = thePosition; }

        // dereferencing operators
        constexpr T& operator*() const { return *position; }
        constexpr T* operator->() const { return &*position; }

        // increment
        constexpr iterator& operator++()   // preincrement
        {
            ++position; return *this;
        }
        constexpr iterator operator++(int) // postincrement
        {
            iterator old = *this;
            ++position;
            return old;
        }

        // decrement
        constexpr iterator& operator--()   // predecrement
        {
            --position; return *this;
        }
        constexpr iterator operator--(int) // postdecrement
        {
            iterator old = *this;
            --position;
            return old;
        }

        // equality testing
        bool operator!=(const iterator right) const
        {
            return position != right.position;
        }
        bool operator==(const iterator right) const
        {
            return position == right.position;
        }
    protected:
        T* position;
    };  // end of iterator class

protected:  // additional members of arrayList
    void checkIndex(int theIndex) const;
    // throw illegalIndex if theIndex invalid
    T* element = nullptr;            // 1D array to hold list elements
    int listCapacity = 0;       // capacity of the 1D array
    int listSize = 0;          // number of elements in list
};

template<class T>
constexpr arrayList<T>::arrayList(std::initializer_list<T> initList) {
    for (auto& e : initList) { insert(listSize, e); }
}

template<class T>
constexpr arrayList<T>::arrayList(const arrayList<T>& theList)
{// Copy constructor.
    listCapacity = theList.listCapacity;
    listSize = theList.listSize;
    element = new T[listCapacity];
    copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
    if (theIndex < 0 || theIndex >= listSize) {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template<class T>
constexpr T& arrayList<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
    checkIndex(theIndex);
    return element[theIndex];
}

template<class T>
constexpr int arrayList<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search for theElement
    int theIndex = (int)(find(element, element + listSize, theElement)
        - element);

// check if theElement was found
    if (theIndex == listSize)
        // not found
        return -1;
    else return theIndex;
}

template<class T>
void arrayList<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
    checkIndex(theIndex);

    // valid index, shift elements with higher index
    copy(element + theIndex + 1, element + listSize,
        element + theIndex);

    element[--listSize].~T(); // invoke destructor
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
    if (theIndex < 0 || theIndex > listSize) {// invalid index
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    // valid index, make sure we have space
    if (listSize == listCapacity) {// no space, double capacity
        changeLength1D(element, listCapacity, 2 * listCapacity);
        listCapacity *= 2;
    }

    // shift elements right one position
    copy_backward(element + theIndex, element + listSize,
        element + listSize + 1);

    element[theIndex] = theElement;

    listSize++;
}

template<class T>
void arrayList<T>::output(ostream& out) const
{// Put the list into the stream out.
    copy(element, element + listSize, ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const arrayList<T>& x)
{
    x.output(out); return out;
}

template <class T>
void arrayList<T>::shrink_to_unique_On2()
{
    // This method uses std::unordered_set, an efficient STL container whose implementation
    // is based on concept of hash map (the {VALUE} is omitted, leaving the {KEY}).
    // std::unordered_set shares the same efficiency with std::unordered_map (STL hash map).
    std::unordered_set<T> set;
    // Because I have designed {iterator} for class {arrayList}, most STL methods can be used
    // with {arrayList}. Therefor, following `for(...)` can be substituted for RANGE FOR (C++11),
    // i.e., `for(auto e: this){...}`.
    for (int i = 0; i < listSize;) {
        // If {element[i]} has not been added to {set}:
        if (set.count(element[i]) == 0) {
            // Add {element[i]} to {set}:
            set.emplace(element[i]);
            ++i;
        }
        // Else if {element[i]} has already been in {set}:
        else {
            // Erase the reduplicate element:
            erase(i);
            // After invoking method {erase()}, {listSize} will decrease automatically.
        }
    }
}

template<class T>
void arrayList<T>::shrink_to_unique_On()
{
    std::unordered_set<T> set;
    arrayList<T> temp;
    for (auto e : *this) {
        if (set.count(e) == 0) {
            set.emplace(e);
            temp.push_back(e);
        }
    }
    delete[] element;
    listSize = temp.size();
    listCapacity = temp.capacity();
    element = new T[listCapacity];
    std::copy(temp.begin(), temp.end(), this->begin());
}

template<class T>
void arrayList<T>::reverse()
{
    for (int i = 0; i <= listSize / 2; ++i) {
        std::swap(element[i], element[listSize - 1 - i]);
    }
}

#endif
