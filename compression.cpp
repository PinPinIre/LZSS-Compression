//Cathal Geoghegan
//11347076
#include "compression.h"
#include "BitVector.h"
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <fstream>
using namespace std;

/*
*	Constructor which is passed the number of bits the window and the length will require
*/ 
LZSSCompression::LZSSCompression(int windowBits, int lengthBits)
{	this -> windowBits = windowBits;
	this -> lengthBits = lengthBits;
	bitSize = windowBits + lengthBits;							// The number of bits in a pointer excluding the flag bit
	windowSize = calculateMaxBitSize( windowBits );				// Finds the max window size based on the number of bits allocated
	lengthSize = calculateMaxBitSize(lengthBits);
	storeResults = new BitVector(bitSize + 1);					// Creates the bit vector used in the storing of the bits
}

//Function that goes back through a string and searches for the longest previous string of characters that matches the next string of characters
//Receives the string to search and the current position within that string
//Returns a pointer to a integer array. The first element is the index of the longest substring and the second index is the lenght of the substring
int * LZSSCompression::findPreviousOccurence(string fileString, long currentPosition)
{	
	int * returnArray  = new int[2];
	int currentChar = currentPosition -1;
	int charsForward = 0;
	int maxCharsForward = 0;
	int locationMaxChars= -1;
	int tempCharPointer;
	while(currentChar >= 0 && ((currentPosition - currentChar) < windowSize))						//Loops while not at the start of the string or has gone beyond the window
	{
		if(fileString.at(currentChar) == fileString.at(currentPosition) )							//Will loop forwards through previous substring and the current string 
		{																							//until the chars are not equal or the end of the string is reached
			charsForward = 1;
			tempCharPointer = currentChar + 1;
			while( ((currentPosition + charsForward) < fileString.length()) && (charsForward < lengthSize) && (fileString.at(tempCharPointer) == fileString.at(currentPosition + charsForward)))
			{
				charsForward = charsForward + 1;
				tempCharPointer = tempCharPointer + 1;
			}
			if(charsForward > maxCharsForward)								//Becomes the longest substring if its longer than the previous substring
			{
				maxCharsForward = charsForward;
				locationMaxChars = currentPosition - currentChar;
			}
		}
		currentChar = currentChar - 1;
	}
	returnArray[0] = locationMaxChars;
	returnArray[1] = maxCharsForward;
	return returnArray;
}

// 	Function that is passed the number of bits used to represent the max ofset
//	This is used to calculate the max window size
int LZSSCompression::calculateMaxBitSize(int bits)
{
	return pow(2,bits) -1;
}

//A function that is passesd a file name and attempts to compress that file
//Returns a human readable format of the compressed string
string LZSSCompression::compressFile(string fileName, string outputfileName)
{
	int pointer;
	string outputString = "";
	string wholeString = "";
	string currentLine = "";
	fstream infile;
	ofstream outfile;
	long filePointer = 0;
	int * lengthAndOffset;
	infile.open(fileName.c_str(), ios::in);
	outfile.open(outputfileName.c_str(), ios::binary);
	getline(infile, currentLine);
	while(infile)												//Reads in the full file at once in order to reduce disk reads. This is not memory efficient and would not be
	{															//suitable for compressing very large files. Trade off between time and memory
		wholeString = wholeString + currentLine + "\n";			//Replaces new line characters.
		getline(infile, currentLine);
	}
	infile.close();

	originalBytes = wholeString.length();						//Size of the original file is the lenght of the read in string
	while(filePointer < wholeString.length())
	{
		lengthAndOffset = findPreviousOccurence(wholeString, filePointer);		//Finds any previous occurences of the next substring
		if(lengthAndOffset[0] != -1 && lengthAndOffset[1] > 1)					//Stores the pointer if the location is valid and the length is greater than 1
		{
			pointer = lengthAndOffset[0] << lengthBits;
			pointer = pointer | lengthAndOffset[1];
			storeResults -> addElement(0, pointer, outfile);
			numberOfBits = numberOfBits + bitSize + 1;							//Adds the size of the pointer plus the flag
			filePointer = filePointer + lengthAndOffset[1];
		}
		else
		{
			pointer = 0;
			pointer = pointer + wholeString.at(filePointer);
			storeResults -> addElement(1, pointer, outfile);
			filePointer = filePointer + 1;
			numberOfBits = numberOfBits + 8 + 1;							//Adds the size of the pointer plus the flag
		}
		delete lengthAndOffset;												//Deallocates memory to the array returned by the findPreviousOccurence function
	}
	storeResults -> flushToFile(outfile);
	outfile.close();
	return outputString;
}

//Function that is passed an int value and returns the string representation of the string
string LZSSCompression::to_String(int number)
{
	stringstream temp;
	temp << number;
	return temp.str();
}