#pragma once
#include<vector>

/**
 * @brief Find the index of the element that has the value {key}
 * in an iterative way in {vec} if it exists, -1 otherwise.
*/
template<class ElemTy>
int BinarySearch(const std::vector<ElemTy>& vec, const ElemTy& key) {
    int low = 0;
    int high = (int)vec.size() - 1;
    while (low <= high) {
        int mid = ((high - low) >> 1) + low;
        if (vec[mid] == key) {
            return mid;
        } else if (vec[mid] > key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

/**
 * @brief Find the index of the element that has the value {key}
 * in an recursive way in {vec} if it exists, -1 otherwise.
*/
template<class ElemTy>
int BinarySearch(const std::vector<ElemTy>& vec, int low, int high, const ElemTy& key) {
    if (low > high) { return -1; }
    int mid = ((high - low) >> 1) + low;
    if (vec[mid] > key) {
        mid = BinarySearch(vec, low, mid - 1, key);
    } else if (vec[mid] < key) {
        mid = BinarySearch(vec, mid + 1, high, key);
    }
    return mid;
}

/**
 * @brief Find an iterator pointing to the element that has the value {key}
 * in the range [{begin}, {end}) if it exists, {end} otherwise.
*/
template<class InputIt, class ElemTy>
auto BinarySearch(InputIt begin, InputIt end, const ElemTy& key) {
    int length = std::distance(begin, end);
    while (length > 0) {
        InputIt midIter = begin;
        int step = length / 2;
        std::advance(midIter, step);
        if (*midIter == key) {
            return midIter;
        } else if (*midIter > key) {
            length = step;
        } else {
            length -= step + 1;
            begin = ++midIter;
        }
    }
    return end;
}
