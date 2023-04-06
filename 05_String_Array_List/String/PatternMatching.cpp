#include"KMP.h"
#include"String.h"
#include"BruteForce.h"

void PatternMatching() {
    String target = "abbababbaaabaabbbbababa";
    String pattern = "aba";
    std::vector<int> vec1 = BruteForce(target, pattern);
    std::vector<int> vec2 = KMP(target, pattern);
    for (const auto& i : vec1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (const auto& i : vec2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}