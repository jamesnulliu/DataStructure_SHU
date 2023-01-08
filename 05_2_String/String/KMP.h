#pragma once
#include "String.h"

int* getNext(const String& p)
{
    int j = 0;
    int k = -1;
    int size = p.length();
    int* next = new int[size] {-1};
    while (j < size - 1) {
        if (k == -1 || p[j] == p[k]) {
            next[j] = k;
            j++;
            k++;
        } else {
            k = next[k];
        }
    }
    return next;
}

int KMP(const String& T, const String& p)
{
    int i = 0;
    int j = 0;
    int* next = getNext(T);
    while (i < T.length() && j < p.length()) {
        if (j == -1 || T[i] == p[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j == p.length()) {
        return i - j;
    }
    delete[] next;
    return -1;
}
