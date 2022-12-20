#define use_length
#include "../header/arrayQueue.h"

void test_length()
{
    arrayQueue<int> a(2);
    std::cout << "Use {length}:\t";
    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    while (!a.empty()) {
        std::cout << a.front() << ' ';
        a.pop();
    }
    std::cout << "Queue empty!" << std::endl;
}