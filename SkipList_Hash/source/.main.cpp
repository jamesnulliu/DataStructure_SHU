#include <iostream>
#include <utility>
#include "../header/LZW_compression.h"
#include <fstream>

std::ofstream otest;

int main(int argc, char* argv[]) {
	LZW_compress(argc, argv);
	std::cin.get();
}