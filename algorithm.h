/*
* This file reads in a binary input or converts sent info to binary then randomly hides provided data inside the binary
* author: Kayvan Ehteshami
*
*/

#include "stdafx.h"
#include <bitset>
#include <ctime>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Algorithm {
public:
	//Prototypes
	vector<char> encryptToBinary(char*);
	vector<char> hide();
	void find();
	std::string* getPD();
	vector<char> getBinary();
	vector<char> getNonBinaryData();

	//long is the largest number related data type
	//No clue how large these will be so need largest possible
	long systime;
	long dataSize;
	long varNumb;

	vector<char> binaryData;

	//Only accepting First Name, Last Name, Birthday, Social Security, Address, Primary Car Physician, Medical History
	std::string personalData[7] = { "" };

	//Empty Constructor just incase
	Algorithm();

	//Constructor to accept binary data alongside personal data
	Algorithm(const std::string binary, std::string pD[]);

	//If given non-binary data
	Algorithm(const char * encryption, std::string pD[]);
};
