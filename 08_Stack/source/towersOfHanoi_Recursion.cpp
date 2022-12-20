// Towers of Hanoi by Recursion
// Move n disks from the top of x to the top of y, and use tower z as intermedia.
// Time complexity: жи(2^n)
// Steps: 2^n - 1 

#include <iostream>

void towerOfHanoi(int n, int x, int y, int z) {
	if (n > 0) {
		// First, move (n - 1) disks from the top of x to the top of z, and use y as intermedia.
		towerOfHanoi(n - 1, x, z, y);
		// Second, move the rest one disk from x to y.
		std::cout << "Move top disk from tower " << x << " to top of tower " << y << std::endl;
		// Third, move (n - 1) disks from the top of z to the top of y, and use x as intermedia.
		towerOfHanoi(n - 1, z, y, x);
	}
}