// Print the matched parenthesis' index and the unmatched's.
// Time complexity жи(n) 

#include <iostream>
#include "../class/linkedStack.h"
void printMatchedPairs(std::string expr) {
	linkedStack<int> s;
	int length = (int)expr.size();
	// scan through expr to search "(" and ")"
	for (int i = 0; i < length; i++) {
		if (expr.at(i) == '(') {
			s.push(i);
		}
		else {
			if (expr.at(i) == ')') {
				try {
					std::cout << s.top() << ' ' << i << std::endl;
					s.pop();
				}
				catch (stackEmpty) {
					std::cout << "No match for right parenthesis" << " at " << i << std::endl;
				}
			}
		}
		while (!s.empty()) {
			std::cout << "No match for left parenthesis at " << s.top() << std::endl;
			s.pop();
		}
	}
}