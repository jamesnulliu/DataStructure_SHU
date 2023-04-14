#include<vector>
#include<iostream>
#include<algorithm>
#include"LinearSearch.h"
#include"BinarySearch.h"

void SearchTest() {
    std::vector<int> vec{ 1,9,4,6,2,3,-9,10,3,5 };

    std::ranges::sort(vec);
    for (const auto& i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    auto iter = BinarySearch(vec.begin(), vec.end(), 11);
    if (iter != vec.end()) {
        std::cout << *iter << " found" << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
}