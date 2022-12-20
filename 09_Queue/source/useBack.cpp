#include "../header/arrayQueue.h"

void test_back()
{
    arrayQueue<int> a(2);
    std::cout << "Use {back}:\t";
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