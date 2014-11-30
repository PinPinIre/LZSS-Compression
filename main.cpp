//Cathal Geoghegan
#include "BitVector.h"
#include "decompress.h"
#include "compression.h"
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <fstream>
using namespace std;



// A function that calculates the number of bytes needed to store a number of bits
int calculateBytes(int bits)
{
	int bytes = bits / 8;
	if ( (bits % 8) == 0 )
	{
		bytes = bytes + 1;
	}
	return bytes;
}

// A function that receives a float and returns the string representation
string floatToString(float number)
{
	stringstream temp;
	temp << number;
	return temp.str();
}


int main(int argc, char const *argv[])
{
	int offset_bits = 7;
	int length_bits = 4;
	float percentage;
	char * file;

	if(argc < 2)
	{
		cerr << "Valid file name expected as argument" << endl;
		return 1;
	}
	// Probably should have done something with these arguments
	cout << argv[0] <<endl;
	cout << argv[1] <<endl;
	cout << argv[2] <<endl;
	cout << argv[3] <<endl;
	return 1;


	LZSSCompression test(offset_bits, length_bits);										//First value is the window size and second is the length
	string testString = test.compressFile("FrankTest.txt", "outFile.bin");
	cout << "\nOrginal Size " << test.originalBytes << endl;
	cout << "Compressed Size " << calculateBytes( test.numberOfBits ) << endl;
	percentage = (((float)calculateBytes( test.numberOfBits ))/((float)test.originalBytes)) * 100.0;
	cout << "Percentage of original: " << floatToString(percentage) << endl ;

	LZSSDecompression testing(offset_bits, length_bits);
	string decompressedFile = testing.decompressFile("outFile.bin");
	cout << "Decompressed File: " << endl;
	cout << decompressedFile << endl;
	cout << "Program end!" << endl;

	return 0;
}
