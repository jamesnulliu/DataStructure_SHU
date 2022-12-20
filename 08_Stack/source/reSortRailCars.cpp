// Re-sort Rail Cars
// Time complexity: жи(numberOfTracks*numberOfCars)]	

#include "../class/arrayStack.h"

// Global variable:
arrayStack<int>* track; // The array of holding track.
int numberOfCars;
int numberOfTracks;
int smallestCar; // The car with the smallest code in holding tracks.
int itsTrack; // The holding track which holds the smallestCar.

// Move a car to a holding track;
// Return false only when there is no available holding track.
bool putInHoldingTrack(int);

// Move the smallesCar from holding track to ouputTrack.
void outputFromHoldingTrack();

bool railroad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks) {
	// Re-sort the cars in initial sequence;
	// Return true when succeed, otherwise false.

	numberOfCars = theNumberOfCars;
	numberOfTracks = theNumberOfTracks;
	// Create the stacks of buffer tracks.
	track = new arrayStack<int>[numberOfTracks + 1];
	
	int nextCarToOutput = 1;

	// Initial smallestCar with an invalid number when no car is in holding track.
	// ATTENTION: smallestCar is invalid at first, 
	// and could be allocated a vaild number only after executing function outputFromHoldingTrack().
	smallestCar = numberOfCars + 1;

	// Re-sort the cars.
	for (int i = 1; i <= numberOfCars; i++) {
		if (inputOrder[i] == nextCarToOutput) {
			// Move the already-sorted car to output track.
			std::cout << "Move car " << inputOrder[i] << " from input track to output track" << std::endl;
			nextCarToOutput++;

			// When the smallestCar does be in a holding track.
			while (smallestCar == nextCarToOutput) {
				outputFromHoldingTrack();
				nextCarToOutput++;
			}
		}
		else {
			// Move car i to a holding track.
			if (!putInHoldingTrack(inputOrder[i])) {
				return false;
			}
		}
	}
	return true;
}

void outputFromHoldingTrack() {
	// delete the smallesCar from the stack of the holding track.
	track[itsTrack].pop();
	std::cout << "Move car " << smallestCar << " from holding track " << itsTrack 
		<< " to output track" << std::endl;
	// Allocate a nonexsist number to the smallestCar.
	smallestCar = numberOfCars + 2;
	// Check the top of all the stacks, find the smallestCar and it's itsTrack.
	for (int i = 1; i <= numberOfTracks; i++) {
		if (!track[i].empty() && (track[i].top() < smallestCar)) {
			smallestCar = track[i].top();
			itsTrack = i;
		}
	}
	// If ultimately not found a new smallest car, it shows there is no smaller car in holding tracks.
}

bool putInHoldingTrack(int c) {
	// Initialization.
	int bestTrack = 0, bestTop = numberOfCars;
	// Scan holding tracks.
	for (int i = 1; i <= numberOfTracks; i++) {
		// If track[i] is not empty.
		if (!track[i].empty()) {
			int topCar = track[i].top();
			// Move if c is smaller then the top of the track as well as numberOfCars(bestTop).
			if (c < topCar && topCar <= bestTop) {
				// Move c to the holding track.
				bestTop = topCar;
				bestTrack = i;
			}
		}
		// If track[i] is empty.
		else {
			if (bestTrack == 0) {
				bestTrack = i;
			}
		}
	}
	// If there is no available track, return false.
	if (bestTrack == 0) {
		return false;
	}
	// Move car c to bestTrack.
	track[bestTrack].push(c);
	std::cout << "Move car " << c << " from input track to holding track " << bestTrack << std::endl;
	// If necessary, update smallestCar and itsTrack.
	if (c < smallestCar) {
		smallestCar = c;
		itsTrack = bestTrack;
	}
	return true;
}