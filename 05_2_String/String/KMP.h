#pragma once
#include <string>
#include <vector>
#include "String.h"

inline void getNext(std::vector<int>& next, const String& pattern)
{
    next.clear();
    next.push_back(-1);
    for (int i = 0, j = -1; i < (int)pattern.size();) {
        if (j == -1 || pattern[i] == pattern[j]) {
            ++i, ++j;
            if (i != (int)pattern.size() && pattern[j] == pattern[i]) {
                next.push_back(next[j]);
            } else {
                next.push_back(j);
            }
        } else {
            j = next[j];
        }
    }
}

inline std::vector<int> KMP(const String& target, const String& pattern)
{
    int i = 0;
    int j = 0;
    std::vector<int> next;
    getNext(next, pattern);
    std::vector<int> result;

    while (i < (int)target.size() && j < (int)pattern.size()) {
        if (j == -1 || target[i] == pattern[j]) {
            ++i;
            ++j;
            if (j == (int)pattern.size()) {
                result.push_back(i - j);
                j = next[j];
            }
        } else {
            j = next[j];
        }
    }
    return result;
}
inline void getNext(std::vector<int>& next, const std::string& pattern)
{
    next.clear();
    next.push_back(-1);
    for (int i = 0, j = -1; i < (int)pattern.size();) {
        if (j == -1 || pattern[i] == pattern[j]) {
            ++i, ++j;
            if (i != (int)pattern.size() && pattern[j] == pattern[i]) {
                next.push_back(next[j]);
            } else {
                next.push_back(j);
            }
        } else {
            j = next[j];
        }
    }
}

inline std::vector<int> KMP(const std::string& target, const std::string& pattern)
{
    int i = 0;
    int j = 0;
    std::vector<int> next;
    getNext(next, pattern);
    std::vector<int> result;

    while (i < (int)target.size() && j < (int)pattern.size()) {
        if (j == -1 || target[i] == pattern[j]) {
            ++i;
            ++j;
            if (j == (int)pattern.size()) {
                result.push_back(i - j);
                j = next[j];
            }
        } else {
            j = next[j];
        }
    }
    return result;
}
