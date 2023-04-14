#pragma once
#include<vector>

/**
 * @brief Find the index of the first element
 * that has the value {key} in {vec} if it exists, -1 otherwise.
*/
template<class T>
int LinearSearch(const std::vector<T>& vec, const T& key) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == key) { return i; }
    }
    return -1;
}

/**
 * @brief Find an iterator pointing to the first element that has the value {key}
 * in the range [{begin}, {end}) if it exists, {end} otherwise.
*/
template<class InputIt, class ElemTy>
InputIt LinearSearch(InputIt begin, InputIt end, const ElemTy& key) {
    for (auto iter = begin; iter != end; iter++) {
        if (*iter == key) { return iter; }
    }
    return end;
}
