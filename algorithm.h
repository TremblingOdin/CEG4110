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

//Prototypes
vector<char> encryptToBinary(char*);
vector<char> hide();
void find();
std::string* getPD();
vector<char> getBinary();
vector<char> getNonBinaryData();

class Algorithm {
public:
	//long is the largest number related data type
	//No clue how large these will be so need largest possible
	long systime;
	long dataSize;
	long varNumb;

	vector<char> binaryData;

	//Only accepting First Name, Last Name, Birthday, Social Security, Address, Primary Car Physician, Medical History
	std::string personalData[7] = { "" };

	//Empty Constructor just incase
	Algorithm() {
		//Set up time and other variables
		tm * tt;
		systime = mktime(tt);
		dataSize = 0;
		varNumb = 7;
	}

	//Constructor to accept binary data alongside personal data
	Algorithm(const std::string binary, std::string pD[]) {
		//Set up time and other variables
		tm * tt;
		systime = mktime(tt);
		varNumb = 7;
		dataSize = sizeof(binary);

		for (int i = 0; i<7; i++)
			personalData[i] = pD[i];

		//Binary.size() returns unsigned
		for (unsigned i = 0; i<binary.size(); i++)
			binaryData.push_back(binary[i]);

	}

	//If given non-binary data
	Algorithm(const char * encryption, std::string pD[]) {
		//Set up time and other variables
		tm * tt;
		systime = mktime(tt);
		varNumb = 7;

		for (int i = 0; i<7; i++)
			personalData[i] = pD[i];

		encryptToBinary(encryption);

		dataSize = sizeof(binaryData);
	}

	//When given a char array convert it into binary to hide data
	vector<char> encryptToBinary(const char * data) {

		//Until the first character pointed by s is not a null character
		while (*data) {
			binaryData.emplace_back(std::bitset<8>(*data).to_string());
		}
	}

	//Hide the data within the binary and return it all
	vector<char> hide() {
		std::vector<char>::iterator location;

		//Char pointer creator
		const char * binaryPointer = (to_string(systime) + '@' + to_string(dataSize) + '@').c_str();
		location = binaryData.begin();
		//@ indicates end of a thing of info
		while (binaryPointer != NULL) {
			binaryData.insert(location, *binaryPointer);
		}

		for (int i = 0; i < varNumb; i++) {
			binaryPointer = (personalData[i] + '@').c_str();

			long place = (((systime % 10) + i) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5));

			//Rudimentary algorithm
			binaryData.insert(location + place, *binaryPointer);
		}
	}

	//Discover the data within the binary, assign it to the variables so they may be called with getter methods
	void find() {
		std::string systimeString = "";
		std::string dataSizeString = "";

		std::vector<char>::iterator location;
		location = binaryData.begin();

		while (binaryData.at(*location) != '@' || binaryData.at(*location) != NULL) {
			systimeString += binaryData.at(*location);
			binaryData.erase(location);
		}
		binaryData.erase(location);

		if (binaryData.at(*location) == NULL) {
			throw("Improperly formatted or no data");
		}

		systime = std::stoll(systimeString);

		while (binaryData.at(*location) != '@' || binaryData.at(*location) != NULL) {
			dataSizeString += binaryData.at(*location);
			binaryData.erase(location);
		}
		binaryData.erase(binaryData.begin());

		if (binaryData.at(*location) == NULL) {
			throw("Improperly formatted or no data");
		}

		dataSize = std::stoll(dataSizeString);

		for (int i = 0; i < varNumb; i++) {
			long place = ((systime % 10) + i * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1));
			while (binaryData.at(*location + place) != '@' || binaryData.at(*location + place) != NULL) {
				personalData[i] += binaryData.at(*location + place);
				binaryData.erase(location + place);
			}
			binaryData.erase(location + place);
		}
	}

	//Return the personal data
	std::string* getPD() {
		std::string* pdp = personalData;

		return pdp;
	}

	//Return the binary data that originally hid the personal data
	vector<char> getBinary() {
		return binaryData;
	}

	//Return the original non-binary data
	vector<char> getNonBinaryData() {
		std::string binaryString(binaryData.begin(), binaryData.end());
		//Cpp has so many useful data libraries
		std::stringstream sstream(binaryString);
		vector<char> nonBinaryData;


		while (sstream.good()) {
			std::bitset<8> bits;
			sstream >> bits;
			char c = char(bits.to_ulong());
			nonBinaryData.emplace_back(c);
		}

		return nonBinaryData;
	}
};
