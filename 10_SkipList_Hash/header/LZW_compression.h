#pragma once

/**
* @brief	The interface of the whole program.
*
* @param	"argc" Argument count.
* @param	"argv[]" Argument vector.
* @code		int main(int argc, char* argv[]){
*				LZW_compress(argc, argv);
*			}
*/
void LZW_compress(int argc, char* argv[]);
/**
* @brief	Establish input and output stream.
*
* @param	"argc" The number of parameters in console.
* @param	"argv[i]" The pointer points to the "i"th parameter.
*/
void setFiles(int argc, char* argv[]);
