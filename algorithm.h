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
	//Empty Constructor just incase
	Algorithm();

	//Constructor to accept binary data alongside personal data
	Algorithm(const std::string binary, std::vector<std::string> pd);

	//If given non-binary data
	Algorithm(char * encryption, std::vector<std::string> pd);

	//Prototypes
	void encryptToBinary(char*);
	vector<char> hide();
	void find();
	std::vector<std::string> getPD();
	vector<char> getBinary();
	vector<char> getNonBinaryData();

	//long is the largest number related data type
	//No clue how large these will be so need largest possible
	long systime;
	long dataSize;
	long varNumb;

	vector<char> binaryData;

	//Only accepting First Name, Last Name, Birthday, Social Security, Address, Primary Car Physician, Medical History
	std::vector<std::string> personalData = { "","","","","","","" };
};
