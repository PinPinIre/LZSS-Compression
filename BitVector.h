//Cathal Geoghegan
//11347076
#ifndef BIT_VECTOR_H
#define BIT_VECTOR_H
#include <fstream>
using namespace std;

class BitVector 
{
private:
	char * bitArrays;										// Byte array of bits
	int sizeVector;
	int currentElement;										// Current element in the byte array
	int currentBitPosition;									// Current bit in the current element
	int sizePointer;										// The number of bits in each pointer
	void insertBit(int bit);
public:	
	BitVector(int bitSize);
	const static int BYTE_SIZE = 8;
	void addElement(int flag, int pointerOrChar, ofstream& writeFile);
	static int lcm(int number1, int number2);
	static int gcd(int number1, int number2);
	int issolateBit(int number, int position);
	int issolateBit(char number, int position);
	void flushToFile(ofstream& writeFile);	
	int * getElement(fstream& readFile);
	int getNextBit();
	void prepareForFileRead(fstream& readFile);
	void printStateOFVector();
};

#endif