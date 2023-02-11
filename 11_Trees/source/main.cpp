#include <iostream>
#include <stack>
#include <exception>

int main() {
    std::stack<int> s;
    try {
        s.top();
    } catch(std::exception e) {
        std::cout << e.what();
    }
}