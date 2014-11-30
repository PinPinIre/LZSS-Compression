//Cathal Geoghegan
//11347076
#include "BitVector.h"
#include <iostream>

/*
* Constructor that constructs a bit vector that is the size of the lowest common multiple of the size of a pointer and the size of a byte
*/
BitVector::BitVector(int bitSize) 
{	
	sizeVector = lcm(BYTE_SIZE + 1, bitSize);							// bit vector is the size of lcm of the size of a char and a pointer.
	bitArrays = new char [sizeVector];
	currentElement = 0;
	sizePointer = bitSize;
	currentBitPosition = 0;
	for(int i = 0; i < sizeVector; i++) 		
	{
			bitArrays[i] = 0;											// Cleans the memory of the bit vector
	}
}

/*
* Function that adds a pointer or a character to the bit vector and writes it to the stream if the bit vector is full
*/
void BitVector::addElement(int flag, int pointerOrChar, ofstream& writeFile)
{
	int counter;
	int insert_Bit;
	insertBit(flag);
	if(currentElement == sizeVector)	
	{	//If the bit vector is full, it is written to the file and the bit vectors memory is cleaned
		//write the vector to file
		writeFile.write ( bitArrays, sizeVector);
		currentElement = 0;
		currentBitPosition = 0;
		for(int i = 0; i < sizeVector; i++) 		
		{
			bitArrays[i] = 0;
		}
	}
	if( flag == 1) 													//Char
	{
		counter = BYTE_SIZE -1;
	}
	else 
	{
		counter = sizePointer -2;									//Minus 2 as bit 1 is flag and extra bit becuase it's treated as a zero indexed array
	}
	for( int i = counter; i >= 0; i--)						
	{
		insert_Bit = issolateBit(pointerOrChar, i);					// Issolates the current bit in the pointer
		insertBit(insert_Bit);										// Inserts the curent bit into the bit vector
		if(currentElement == sizeVector)	
		{	//If the bit vector is full, it is written to the file and the bit vectors memory is cleaned
			//write the vector to file
			writeFile.write ( bitArrays, sizeVector);
			currentElement = 0;
			currentBitPosition = 0;
			for(int i = 0; i < sizeVector; i++) 		
			{
				bitArrays[i] = 0;
			}
		}	
	}	

}

/*
* A function that retrieves the current pointer from the bit vector
* An array is returned with the flag as the first element and the second element as to the data(which could be character data or pointer data)
*/
int * BitVector::getElement(fstream& readFile)
{
	int counter;
	int flag;
	int pointer;
	int * returnArray = new int[2];										// The return array
	flag = getNextBit();
	if(currentElement == sizeVector)									// If the end of the bit vector has been reached, new data is read into the bit vector
	{
		readFile.read( bitArrays, sizeVector);
		currentElement = 0;
		currentBitPosition = 0;
	}
	if( flag == 1) 														//Char
	{
		counter = BYTE_SIZE;
	}
	else 
	{
		counter = sizePointer -1;										//Minus 2 as bit 1 is flag and extra bit becuase it's treated as a zero indexed array
	}
	pointer = 0;
	for( int i = 0; i < counter; i++) {									// gets the pointer or character data from the bit vector
		pointer = pointer << 1;
		pointer = pointer | getNextBit();
		if(currentElement == sizeVector)								// If the end of the bit vector has been reached, new data is read into the bit vector
		{
			readFile.read( bitArrays, sizeVector);
			currentElement = 0;
			currentBitPosition = 0;
		}
	}
	returnArray[0] = flag;
	returnArray[1] = pointer;	
	return returnArray;					
}

// This function retrieves the bit in a specific position in an integer.
int BitVector::issolateBit(int number, int position) 
{
	number = number >> position;
	return number & 1;
}

// This function retrieves the bit in a specific position in a byte.
int BitVector::issolateBit(char number, int position) 
{
	number = number >> position;
	return number & 1;
}

// Inserts a bit into the bit vector
void BitVector::insertBit(int bit) 
{
	unsigned char tempBit = char(bit);						
	tempBit = tempBit << currentBitPosition;						// Shifts bit to correct position
	bitArrays[currentElement] = tempBit | bitArrays[currentElement];// Inserts bit into bit vector
	currentBitPosition++;
	if(currentBitPosition == 8)										//Reached the end of the current byte						
	{
		currentBitPosition = 0;										//Resets the index
		currentElement = currentElement + 1;						//Points to the next byte in the byte array
	}
}

// Function that retrives the next bit from the bit vector 
int BitVector::getNextBit()
{
	int returnInt = bitArrays[currentElement];
	returnInt = returnInt >> currentBitPosition;

	currentBitPosition = currentBitPosition + 1;
	if(currentBitPosition == BYTE_SIZE)								//If the end of the current element moves onto the next element 
	{
		currentElement++;
		currentBitPosition = 0;
	}

	return returnInt & 1;											//Returns only the first bit
}

//	If there are any bits left in the bit vector, they are flushed to the file.
void BitVector::flushToFile(ofstream& writeFile)
{
	//Flush contents of the bit vector to the file
	writeFile.write ( bitArrays, sizeVector);
}

// Reads in first portion of the file and sets the pointers for reading
void BitVector::prepareForFileRead(fstream& readFile)
{
	readFile.read( bitArrays, sizeVector);
	currentElement = 0;
	currentBitPosition = 0;
}

// Function that finds the greatest common denominator of two numbers
int BitVector::gcd( int number1, int number2)
{
	int temp;
	while(number2 != 0) 
	{
		temp = number2;
		number2 = number1 % temp;
		number1 = temp;
	}
	return number1;
}

// Function that finds the lowest common multiple of two numbers
int BitVector::lcm(int number1, int number2) 
{
	return (number1 * number2) / gcd(number1, number2);
}

// Function that prints out the state of the bit vector.
void BitVector::printStateOFVector()
{
	for(int i = 0; i < sizeVector; i++)
	{
		for(int j = BYTE_SIZE-1; j >= 0; j-- )
		{
			printf("%d", (bitArrays[i] >> j) & 1 );
		}
		printf("\n");
	}
	cout << endl;
	cout << endl;
	cout << endl;
}
