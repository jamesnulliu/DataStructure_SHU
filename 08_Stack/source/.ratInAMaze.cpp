// rat in a maze

#define VERSION "0.1"

#include"../class/arrayStack.h"
#include <Windows.h>

int size = 5;
bool maze[10][10];

extern void windowConfig();

/*
* Output text in specific style.
* 
* @text			text to be output
* @font			text color:{blue, green, red, yellow, pink, cyan, white}, default white
* @fI			intensify text, yes:{true}, no:{flase}
* @background	background color:{blue, green, red, yellow, pink, cyan}, default none
* @bI			intensify background, yes:{true}, no:{flase}
*/
extern void textOutput(const char* text, const char* font, bool fI, const char* background, bool bI);
extern void textOutput(const char* text, const char* font, const char* background);
extern void textOutput(const char* text, const char* font);
extern void textOutput(const char* text);
extern void lClick(POINT&, bool);

void welcome() {
	windowConfig();
	for(int i=0;i<100;i++) textOutput("*", "green");
	textOutput("\n");
	for (int i = 0; i < 37; i++) textOutput("*", "red");
	textOutput("  WELCOME TO RAT IN MAZE  ", "yellow");
	for (int i = 0; i < 37; i++) textOutput("*", "red");
	textOutput("\n");
	for (int i = 0; i < 100; i++) textOutput("*", "green");
	textOutput("\n");
	for (int i = 0; i < 33; i++) textOutput(" ");
	textOutput("------ Made By  JamesNULLiu ------\n\n");
	textOutput(">>> ", "green"); textOutput("Algorithms: Deep-First-Search & Backtracking\n", "white");
	textOutput(">>> ", "green"); textOutput("Version: ", "white"); textOutput(VERSION, "yellow");
	for (int i = 0; i < 8; i++) textOutput("\n");
	for (int i = 0; i < 40; i++) textOutput(" ");
	textOutput(" Click Here to Start!\n", "white", "red");
	POINT coor; coor.x = 0; coor.y = 0;
	lClick(coor, false);
	if (coor.y == 14 && coor.x >= 42 && coor.x <= 63) {
		std::cout << "yes" << std::endl;
	}
}


class position {
public:
	int row;
	int col;
	position(int r = 0, int c = 0) :row(r), col(c) {}
};

// Global variable, stores the path to the exit.
arrayStack<position>* path;

// Deep-First-Search & Backtracking & Stack
// Time complexity: жи(size^2)
bool findPath() {
	// Find a path from (1,1) to (size,size).
	// If found, return true, otherwise false.
	path = new arrayStack<position>;
	// Initialize the offsets, showing the increment of the coordinate when moving.
	position offset[4];
	offset[0].row = 0; offset[0].col = 1; // RIGHT
	offset[1].row = 1; offset[1].col = 0; // DOWN
	offset[2].row = 0; offset[2].col = -1; // LEFT
	offset[3].row = -1; offset[3].col = 0; // UP
	//Initialize outer obstacal wall in the maze.
	for (int i = 0; i <= size + 1; i++) {
		maze[0][i] = maze[size + 1][i] = 1;
		maze[i][0] = maze[i][size + 1] = 1;
	}
	// Create here and initialize starting point (1,1).
	position here(1, 1);
	// Starting point set to obstacle, prevent return to start.
	maze[1][1] = 1;
	// Next step, from RIGHT to UP.
	int option = 0;
	int lastOption = 3;
	// Find a path.
	while (here.row != size || here.col != size) {
		// Not reach the exit.
		// Find a step around here moving to.
		int r, c;
		while (option <= lastOption) {
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0) {
				break;
			}
		}
		option++; // Next choice.
		// Judge whether aroud step is found.
		if (option <= lastOption) {
			// Store here to path.
			path->push(here);
			// Move to maze[r][c].
			here.row = r;
			here.col = c;
			// Here set to obstacle, prevent return.
			maze[r][c] = 1;
			option = 0; // Option return to RIGHT
		}
		else {
			// There is no way to go, return to last point.
			if (path->empty()) {
				// There is no point can return.
				return false;
			}
			position next = path->top();
			path->pop();
			if (next.row == here.row) {
				option = 2 + next.col - here.col;
			}
			else {
				option = 3 + next.row - here.row;
			}
		}
	}
	return true;
}