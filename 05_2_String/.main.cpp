#include <string>
#include <iostream>
#include "String/String.h"
#include "String/KMP.h"

int main() {
    String str1 = "aabbccddeeddccbbaa";
    String str2 = "deed";
    std::cout << KMP(str1, str2);

    std::cin.get();
}