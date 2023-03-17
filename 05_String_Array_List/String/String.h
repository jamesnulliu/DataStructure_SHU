#pragma once
#include <cstring>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>

constexpr auto INITIAL_CAPACITY = 10;

class String; // declaration

std::ostream& operator<<(std::ostream& out, const String& str);
std::istream& operator>>(std::istream& in, String& str);

class String
{
public:
    String(int capacity = INITIAL_CAPACITY);
    String(const char* str);
    String(const std::string& str);
    String(const String& str);
    String& operator=(const String& str);
    ~String();

    bool        empty()    const { return !_size; }
    int         size()     const { return _size; }
    int         length()   const { return _size; }
    int         capacity() const { return _capacity - 1; }
    const char* c_str()    const { return _element; }
    char        front()    const { return _element[0]; }
    char        back()     const { return _element[_size - 1]; }

    class       iterator;
    iterator    begin() { return _element; }
    iterator    end() { return _element + _size; }
    char        get(iterator thePosition);
    char& operator[](int thePosition);
    void        erase(iterator thePosition);
    void        insert(iterator thePosition, char ch);
    void        push_back(char ch);

    class       const_iterator;
    using cIterator = const_iterator;
    cIterator   begin()                     const { return _element; }
    cIterator   end()                       const { return _element + _size; }
    const char  get(cIterator thePosition)  const;
    const char  operator[](int thePosition) const;

    bool operator<(const String& str)  const { return strcmp(this->c_str(), str.c_str()) < 0; }
    bool operator<=(const String& str) const { return strcmp(this->c_str(), str.c_str()) <= 0; }
    bool operator==(const String& str) const { return strcmp(this->c_str(), str.c_str()) == 0; }
    bool operator>=(const String& str) const { return strcmp(this->c_str(), str.c_str()) >= 0; }
    bool operator>(const String& str)  const { return strcmp(this->c_str(), str.c_str()) > 0; }

    String operator+(const String& str) const;
    String operator+=(const String& str);

    std::istream& getline(std::istream& in) {
        std::string temp;
        std::getline(in, temp);
        (*this) = temp;
        return in;
    }

    class iterator
    {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef char value_type;
        typedef ptrdiff_t difference_type;
        typedef char* pointer;
        typedef char& reference;
    public:
        iterator(pointer thePosition = nullptr) {
            _position = thePosition;
        }

        reference operator*()  const { return *_position; }
        pointer   operator->() const { return &*_position; }

        iterator& operator++() {
            ++_position;
            return *this;
        }
        iterator operator++(int) {
            iterator old = *this;
            ++_position;
            return old;
        }
        iterator operator+(difference_type diff) {
            return (_position + diff);
        }

        iterator& operator--() {
            --_position;
            return *this;
        }
        iterator operator--(int) {
            iterator old = *this;
            --_position;
            return old;
        }
        iterator operator-(difference_type diff) {
            return (_position - diff);
        }

        bool operator!=(const iterator right) const {
            return _position != right._position;
        }
        bool operator==(const iterator right) const {
            return _position == right._position;
        }

    protected:
        pointer _position;
    };

    class const_iterator : public iterator
    {
    public:
        const_iterator(pointer thePosition = nullptr) : iterator(thePosition) {}
        const iterator::reference operator*()  const { return *(iterator::_position); }
        const iterator::pointer   operator->() const { return &*(iterator::_position); }
    };

private:
    char* _element = nullptr;
    int   _capacity = 0;
    int   _size = 0;
};
