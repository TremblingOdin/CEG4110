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
	std::string personalData [7];

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
	Hider(const std::string binary, std::string pD[]) {
		//Set up time and other variables
		time_t tt;
		systime = * localtime(&tt);
		varNumb = 7;
		dataSize = sizeof(binary);

		personalData = pD;
		binaryData = binary;
		
	}

	//If given non-binary data
	Hider(const char * encryption, std::string pd[]) {
		//Set up time and other variables
		time_t tt;
		systime = * localtime(&tt);
		varNumb = 7;

		personalData = pD;
		encryptToBinary(encryption);

		dataSize = sizeof(binaryData);
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
		//@ indicates end of a thing of info
		binaryData.insert(binaryData.begin(), to_string(systime) + "@" + to_string(dataSize) + "@");

		for(int	i = 0; i < varNumb; i++) {
			//Rudimentary algorithm
			binaryData.insert((((systime % 10) + i) * (systime%33))/2 + (dataSize/((systime%3)+5)), personalData[i]+ "@");
		}
	}

	//Discover the data within the binary, assign it to the variables so they may be called with getter methods
	void find() {
		std::string systimeString = "";
		std::string dataSizeString = "";

		long long location = 0;		

		while(binaryData.at(binaryData.begin())!="@"||binaryData.at(binaryData.begin())!=NULL) {
			systimeString += binaryData.at(location);
			binaryData.erase(binaryData.begin());
		}
		binaryData.erase(binaryData.begin());
		
		if(binaryData.at(location) == NULL) {
			throw("Improperly formatted or no data");
		}

		systime = std::stoll(systimeString);

		while(binaryData.at(binaryData.begin())!="@"||binaryData.at(binaryData.begin())!=Null) {
			dataSizeString += binaryData.at(location);
			binaryData.erase(binaryData.begin());
		}
		binaryData.erase(binaryData.begin());

		if(binaryData.at(location) == NULL) {
			throw("Improperly formatted or no data");
		}

		dataSize = std::stoll(dataSizeString);

		for(int i = 0; i < varNumb; i++) {
			location = ((systime%10)+i*(systime%33))/2 + (datasize/((systime%3)+1));
			while(binaryData.at(location)!="@"||binaryData.at(location)!=NULL){
				personalData[i] += binaryData.at(location);
				binaryData.erase(location);
			}
			binaryData.erase(location);
		}
	}

	//Return the personal data
	std::string[] getPD() {
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
