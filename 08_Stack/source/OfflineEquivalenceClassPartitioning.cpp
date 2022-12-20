// Offline Equivalence Class Partitioning
// Time complexity: жи(n+r) 

#include "../class/arrayStack.h"
#include <iostream>

int offlineEquivalenceClassPartitioning() {
	int n, // number of elements
		r; // number of relations
	std::cout << "Enter number of elements" << std::endl;
	std::cin >> n;
	if (n < 2) {
		std::cout << "Too fiew elements." << std::endl;
		return 1;
	}
	std::cout << "Enter number of relations." << std::endl;
	std::cin >> r;
	if (r < 1) {
		std::cout << "Too few relations." << std::endl;
		return 1;
	}

	// Establish a array with stack, abandon stack[0].
	arrayStack<int>* list = new arrayStack<int>[n + 1];
	// Input r relations and store them in the list.
	int a, b; // (a,b) is a pair of relation.
	for (int i = 1; i <= r; i++) {
		std::cout << "Enter next relation/pair" << std::endl;
		std::cin >> a >> b;
		list[a].push(b);
		list[b].push(a);
	}
	// UnprocessedList holds a series of elements in a list;
	// Every elements in the list will be used as the index.
	arrayStack<int> unprocessedList;
	// Initialize in order to output equivalence class.
	bool* out = new bool[n + 1];
	for (int i = 1; i <= n; i++) {
		// Initialize every elements' output status to flase, indicating "not outputed".
		out[i] = false;
	}
	// Output equivalence class.
	for (int i = 1; i <= n; i++) {
		// Judge whether outputed.
		if (!out[i]) {
			// Start a new class.
			// "i" is the first element in the class, meanwhile being the seed.
			std::cout << "Next class is: " << i << " ";
			// "i"'s output status switch to "true".
			out[i] = true;
			unprocessedList.push(i);
			// Fetch rest elements from unprocessedList.
			while (!unprocessedList.empty()) {
				int j = unprocessedList.top();
				unprocessedList.pop();
				// The elements in list belongs to the same class.
				while (!list[j].empty()) {
					int q = list[j].top();
					list[j].pop();
					// If not outputed.
					if (!out[q]) {
						std::cout << q << " ";
						out[q] = true;
						unprocessedList.push(q);
					}
				}
			}
			std::cout << std::endl;
		}
	}
	std::cout << "End of list of equivalence classes." << std::endl;

	return 0;
}