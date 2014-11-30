//Cathal Geoghegan
#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

#include "BitVector.h"
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <fstream>
using namespace std;

class LZSSDecompression;
class BitVector;

class LZSSDecompression {

public: 							
	string outputString;
	int windowBits;													// The number of chars in a window
	int lengthBits;													
	int bitSize;													// The number of bits in a pointer excluding the flag bit
	string decompressFile(string fileName);							// compresses the file
	LZSSDecompression(int windowBits, int lengthBits);
	string to_String(int number);
private:
	BitVector * storeResults;
};

#endif