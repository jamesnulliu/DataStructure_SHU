#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> vec{ 1,2,34,5,5 };
    auto a = std::ranges::find(vec, 2);
    cout << *a;
}