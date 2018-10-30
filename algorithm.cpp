/*
 * This file reads in a binary input or converts sent info to binary then randomly hides provided data inside the binary
 * author: Kayvan Ehteshami
 *
 */

#include <bitset>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Hider {
	//long long is the largest number related data type
	//No clue how large these will be so need largest possible
	long long systime;
	long long dataSize;
	long long varNumb;

	vector<char> binaryData;
	//Only accepting First Name, Last Name, Birthday, Social Security, Address, Primary Car Physician, Medical History
	//Medical History is limited to 500 characters
	char personalData [7] [500];

	//Prototypes
	vector<char> encryptToBinary(char*);

	//Empty Constructor just incase
	Hider() {
		//Set up time and other variables
		time_t tt;
		systime = * localtime(&tt);
		dataSize = 0;
		varNumb = 7;

		personalData = {"","","","","",""};
	}

	//Constructor to accept binary data alongside personal data
	Hider(const char binary[], char pD[][]) {
		//Set up time and other variables
		time_t tt;
		systime = * localtime(&tt);
		varNumb = 7;
		dataSize = sizeof(binary);

		personalData = pD;
		binaryData = binary[];
		
	}

	//If given non-binary data
	Hider(const char encryption[], char pD[][]) {
		//Set up time and other variables
		time_t tt;
		systime = * localtime(&tt);
		varNumb = 7;
		dataSize = sizeof(binary);

		personalData = pD;
		encryptToBinary(encryption);
	}
	
	//When given a char array convert it into binary to hide data
	void encryptToBinary(char * data) {
		//Small 9 characters buffer
		char output[9];

		//Until the first character pointed by s is not a null character
		while(*data) {
			binaryData.push_back(itoa(*data, output,2); 
		}
	}

	//Hide the data within the binary and return it all
	char[] hide() {
		
	}

	//Discover the data within the binary, assign it to the variables so they may be called with getter methods
	void find() {
		
	}

	//Return the personal data
	char[][] getPD() {
		return personalData;
	}

	//Return the binary data that originally hid the personal data
	vector<char> getBinary() {
		return binaryData;
	}

	//Return the original non-binary data
	vector<char> getNonBinaryData() {
		//Cpp has so many useful data libraries
		std::stringstream sstream(binaryData);
		std::string nonBinaryData;

		
		while(sstream.good()){
			std::bitset<8> bits;
			sstream >> bits;
			char c = char(bits.to_ulong());
			nonBinaryData += c;
		}
		
		return nonBinaryData;
	}
}
