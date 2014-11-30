//Cathal Geoghegan
//11347076
#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "BitVector.h"
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <fstream>
using namespace std;

class LZSSCompression {

public: 
	int originalBytes;												//Number of bytes in the original file
	int numberOfBits;												//Number of bits in the output file
	int windowSize;
	int windowBits;	
	int lengthSize;
	int lengthBits;													//The number of chars in a window
	int bitSize;
	int calculateMaxBitSize(int bits);								// Calculates a window size based on the number of bits
	string compressFile(string fileName, string outputfileName);	// Compresses the file
	static string to_String(int number);							// Converts an int to a string
	LZSSCompression(int windowBits, int lengthBits);
private:
	int * findPreviousOccurence(string fileString, long currentPosition);
	BitVector * storeResults;
};

#endif