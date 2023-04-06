#pragma once
#include <vector>
#include "String.h"

inline std::vector<int> BruteForce(const String& target, const String& pattern) {
    int i = 0;  // Pointer for {target}.
    int j = 0;  // Pointer for {pattern}.
    std::vector<int> result;
    while (i < (int)target.size() && j < (int)pattern.size()) {
        // If the rest of {target} is shorter than {pattern}, then break directly.
        if (j == 0 && (int)target.size() - i < (int)pattern.size()) { break; }
        if (target[i] == pattern[j]) {
            i++, j++;
            if (j != (int)pattern.size()) { continue; }
            result.push_back(i - j);
        }
        i = i - j + 1;
        j = 0;
    }
    return result;
}
