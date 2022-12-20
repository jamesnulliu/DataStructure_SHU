/*****
* HanoiPlus.cpp
*/
#include <vector>

int HanoiPlus(int n, int k) {
	if (k >= n - 1) {
		return 2 * n - 1;
	}
	// Initialize towers and abandon tower[0].
	std::vector<int> tower;
	for (int i = 0; i <= k; i++) {
		tower.push_back(i);
	}
	HanoiPlus_recursion(n, k, tower);
}

void HanoiPlus_recursion(int n, int k,  std::vector<int>& tower) {
	if (n > 0) {
		std::swap(tower[3], tower[2]);
		HanoiPlus_recursion(n - k, k, tower);
		std::swap(tower[1], tower[3]);
		std::swap(tower[2], tower[3]);
		HanoiPlus_recursion(n - k, k, tower);
	}
}