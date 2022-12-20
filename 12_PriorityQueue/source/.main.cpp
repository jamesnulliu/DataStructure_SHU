#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> vec{ 10,4,6,26,3,54,7,8,23,2 };
    std::make_heap(vec.begin(), vec.end(), std::greater<int>());
    std::sort_heap(vec.begin(), vec.end());
    for (auto i : vec) { printf("%d ", i); }
    std::cin.get();
}