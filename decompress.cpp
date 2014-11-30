//Cathal Geoghegan
#include "decompress.h"
#include "BitVector.h"
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <fstream>
using namespace std;

// Constructor which is passed the number of bits the window and the length require 
LZSSDecompression::LZSSDecompression(int windowBits, int lengthBits)
{	this -> windowBits = windowBits;
	this -> lengthBits = lengthBits;
	bitSize = windowBits + lengthBits;							//The number of bits in a pointer excluding the flag bit
	storeResults = new BitVector(bitSize + 1);
}


//A function that is passesd a file name and attempts to decompress that file
// Returns the decompressed file as a string
string LZSSDecompression::decompressFile(string fileName)
{	
	string output = "";
	int * results;					// The pointer and the character data from the bit vector
	int relativePosition;
	int length;
	int lengthMask = 1;
	int currentPosition;
	for(int i = 0; i < lengthBits - 1; i++) 						// Creates lengthMask for the length bits
	{
		lengthMask = lengthMask << 1;
		lengthMask = lengthMask | 1;
	}
	fstream infile;
	infile.open(fileName.c_str(), ios::in); 
	storeResults -> prepareForFileRead(infile);						// Prepares the bit vector for the reading in of the file
	results = storeResults -> getElement(infile);					// Gets the first pointer/char from the bitvector
	while(!infile.fail()) 											// Reads from the file until there is a fail
	{
		if(results[0] == 1)											// 1 flag = char
		{	
			output = output + char(results[1]);						// Stores the char
		}
		else 
		{	
			//Inserts the chars pointed to by the pointer
			relativePosition = results[1] >> lengthBits;
			length = results[1] & lengthMask;
			currentPosition = output.length() -1 ;				
			for(int i = 0; i < length; i++) 
			{
				output = output + output.at(currentPosition - (relativePosition - i -1) );
			}
		}
		delete results;												// Frees results memory 
		results = storeResults -> getElement(infile);
	}
	return output;
}

string LZSSDecompression::to_String(int number)
{
	stringstream temp;
	temp << number;
	return temp.str();
}