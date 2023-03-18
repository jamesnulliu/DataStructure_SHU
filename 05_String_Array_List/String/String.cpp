#include "String.h"

std::ostream& operator<<(std::ostream& out, const String& str)
{
    out << str.c_str();
    return out;
}

std::istream& operator>>(std::istream& in, String& str)
{
    std::string s;
    in >> s;
    str = s;
    return in;
}

String::String(int capacity) : _capacity_vert(capacity), _size(0)
{
    _element = new char[_capacity_vert + 1] {'\0'};
}

String::String(const char* str)
{
    _capacity_vert = (int)strlen(str) + 1;
    _size = (int)strlen(str);
    _element = new char[_capacity_vert] {'\0'};
    strncpy(_element, str, _size);
}

String::String(const std::string& str)
{
    _capacity_vert = (int)str.capacity() + 1;
    _size = (int)str.size();
    _element = new char[_capacity_vert] {'\0'};
    strncpy(_element, str.c_str(), _size);
}

String::String(const String& str)
{
    (*this) = str;
}
String& String::operator=(const String& str)
{
    if (_element == str._element) return *this;
    if (_element != nullptr) delete[] _element;
    _size = str._size;
    _capacity_vert = str._capacity_vert;
    _element = new char[_capacity_vert] {'\0'};
    strncpy(_element, str._element, _size);
    return *this;
}

String::~String()
{
    delete[] _element;
}

char String::get(iterator thePosition)
{
    return *thePosition;
}

char& String::operator[](int thePosition)
{
    return _element[thePosition];
}

void String::erase(iterator thePosition)
{
    std::copy(thePosition + 1, this->end(), thePosition);
    --_size;
    _element[_size] = '\0';
}

void String::insert(iterator thePosition, char ch)
{
    iterator* theRealIterator = new iterator(&*thePosition);
    if (_size + 1 + 1 >= _capacity_vert) {
        int old_capacity = _capacity_vert;
        _capacity_vert *= 2;
        char* temp = new char[_capacity_vert];
        int j = 0;
        for (auto it = this->begin(); it != this->end(); ++it) {
            if (it == thePosition) {
                delete theRealIterator;
                theRealIterator = new iterator(temp + j);
            }
            *(temp + j) = *it;
            ++j;
        }
        if (thePosition == this->end()) {
            delete theRealIterator;
            theRealIterator = new iterator(temp + this->_size);
        }
        delete[] _element;
        _element = temp;
    }
    std::copy_backward(*theRealIterator, this->end(), this->end() + 1);
    // std::copy(thePosition, this->end(), thePosition + 1);
    *(*theRealIterator) = ch;
    ++_size;
    _element[_size] = '\0';
    delete theRealIterator;
}

void String::push_back(char ch)
{
    insert(this->end(), ch);
}

const char String::get(const_iterator thePosition) const
{
    return *thePosition;
}

const char String::operator[](int thePosition) const
{
    return _element[thePosition];
}

String String::operator+(const String& str) const
{
    String result(24);
    for (auto ch : *this) {
        result.push_back(ch);
    }
    for (auto ch : str) {
        result.push_back(ch);
    }
    return result;
}

String String::operator+=(const String& str) {
    for (auto it = str.begin(); it != str.end(); ++it) {
        push_back(*it);
    }
    return *this;
}