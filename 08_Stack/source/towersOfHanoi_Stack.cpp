// Towers of Hanoi by Stack and Recursion
// Move n disks from the top of x to the top of y, and use tower z as intermedia.
// Use stack to simulate the operation.

#include "../class/arrayStack.h"

// tower[1:3] indicates three towers.
arrayStack<int> tower[4];

void moveAndShow(int, int, int, int);
void showState();

void towersOfHanoi(int n) {
	// Preprocessor for moveAndShow().
	for (int d = n; d > 0; d--) {
		// Add d disks to tower[1].
		tower[1].push(d);
	}
	moveAndShow(n, 1, 2, 3);
}

// Also uses Recursion.
void moveAndShow(int n, int x, int y, int z) {
	if (n > 0) {
		moveAndShow(n - 1, x, z, y);
		int d = tower[x].top();
		tower[x].pop();
		tower[y].push(d);
		//showState();
		moveAndShow(n - 1, z, y, x);
	}
}