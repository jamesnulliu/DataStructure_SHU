#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include "../header/HashChains.h"
#include "../header/LZW_compression.h"

/******************************************
* Compression Dictionary expamle:         *
*******************************************
* Code	|0	|1	|2	|3	|4	|5	|6	|7	| *
* Key	|a	|b	|0a	|2b	|1b	|4b	|5a	|3a	| *
*******************************************
* Each code takes 12 bits;                *
* Each key takes 20 bits(12 + char).      *
* So the key can use type long to carry.  *
*******************************************/

constexpr int	DIVISOR = 4099,		// The divisor of the hash chain.
				MAX_CODES = 4096,	// 2^12(each code takes 12 bits)
				BYTE_SIZE = 8,		// There is 8 bits in a byte, and a char takes a bite.
				ALPHA = 256,		// 2^BYTE_SIZE, shows there is 256 different character in a char.
				MASK1 = 255,		// ALPHA - 1
				MASK2 = 15,			// 2^EXCESS - 1, namely "1111" in binary form.
				EXCESS = 4;			// 12 - BYTE_SIZE

typedef std::pair<const long, int> pairType; // pair.first = key, pair.second = code.

int leftOver;				// The bits waiting for being output.
bool bitsLeftOver = false;	// Indicates whether there are bits left.
std::ifstream in;			// Input file.
std::ofstream out;			// Output file.



/**
* @brief	Establish input and output stream, namely "in" and "out".
*
* @param	"argc" The number of parameters in console.
* @param	"argv[i]" The pointer points to the "i"th parameter.
*/
void setFiles(int argc, char* argv[]) {
	// Refer to the ouput file name and input filename.
	char outputFile[50], inputFile[54];
	// Check whether input file name exists and input filename.
	if (argc >= 2) {
		strcpy(inputFile, argv[1]);
	}
	else {
		std::cout << "Enter name of file to compress" << std::endl;
		std::cin >> inputFile;
	}
	// Open binary input file.
	in.open(inputFile, std::ios::binary);
	// IF: failed to open the file.
	if (in.fail()) {
		std::cerr << "Cannot open " << inputFile << std::endl;
		std::cin.get();
		std::cin.get();
		exit(EXIT_FAILURE);
	}
	strcpy(outputFile, inputFile);
	// Add ".zzz" to the output file name.
	strcat(outputFile, ".zzz");
	// Open binary output file.
	out.open(outputFile, std::ios::binary);
}

/**
* @brief	aa
* 
* @param	"pcode" Prefix code.
*/
void output(long pcode) {
	// Output 8 digits, save the rest.
	int c, d;
	// IF: there is left bits before.
	if (bitsLeftOver) {
		d = static_cast<int>(pcode & MASK1);
		c = static_cast<int>((leftOver << EXCESS) | (pcode >> BYTE_SIZE));
		out.put(c);
		out.put(d);
		bitsLeftOver = false;
	}
	// IF: there is no left bits before.
	else {
		leftOver = pcode & MASK2;
		c = static_cast<int>(pcode >> EXCESS);
		out.put(c);
		bitsLeftOver = true;
	}
}

/**
* @brief	L-Z-W compressor.
*/
void compress() {
	// Define and initialize the dictionary.
	hashChains<long, int> h(DIVISOR);
	// Initialize evey single character with code.
	for (int i = 0; i < ALPHA; i++) {
		h.insert(pairType(i, i));
	}
	// Marks the used code.
	int codesUsed = ALPHA;
	// Store a character from input file to "c", in binary form.
	int c = in.get();
	if (c != EOF) {
		long pcode = c; // Prefix code.
		// Get next character from the input file.
		while ((c = in.get()) != EOF) {
			// "theKey" takes 20 bits, 
			// first 12 is code(prefix) and last 8 is next character in the input file.
			// So the following line left shifts 8 bits for "c" which is the next character,
			// and stores all the stuff in "theKey".
			long theKey = (pcode << BYTE_SIZE) + c;
			// Check wether "theKey" is in the dictionary.
			pairType* thePair = h.find(theKey);
			// IF: "theKey" is not in the dictionay.
			if (thePair == nullptr) {
				output(pcode);
				if (codesUsed < MAX_CODES) {
					// Build a new code with key "theKey".
					h.insert(pairType((pcode << BYTE_SIZE) | c, codesUsed++));
				}
				pcode = c;
			}
			else {
				pcode = thePair->second;
			}
		}
		// Output the ultimate code.
		output(pcode);
		if (bitsLeftOver) {
			out.put(leftOver << EXCESS);
		}
	}
	out.close();
	in.close();
}

/**
* @brief	The interface of the whole program.
*
* @param	"argc" Argument count.
* @param	"argv[]" Argument vector.
* @code		int main(int argc, char* argv[]){
*				LZW_compress(argc, argv);
*			}
*/
void LZW_compress(int argc, char* argv[]) {
	setFiles(argc, argv);
	compress();
}