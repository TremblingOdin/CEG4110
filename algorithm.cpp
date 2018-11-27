/*
* This file reads in a binary input or converts sent info to binary then randomly hides provided data inside the binary
* author: Kayvan Ehteshami
*
*/

#include "algorithm.h"
#include <bitset>
#include <ctime>
#include <chrono>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Algorithm::Algorithm() {
	//Set up time and other variables
	__int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	systime = now;
	dataSize = 0;
	varNumb = 8;
}

//Constructor to accept binary data alongside personal data
Algorithm::Algorithm(std::string binary, PersonalData *pd) {
	//Set up time and other variables
	__int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	systime = now;
	varNumb = 8;
	dataSize = sizeof(binary);

	personalData = pd;

	//Binary.size() returns unsigned
	for (unsigned i = 0; i < binary.size(); i++) {
		binaryData = binary;
	}

}

//Constructor for when just given a nonbinary string
Algorithm::Algorithm(std::string unencrypted) {
	varNumb = 8;
	binaryData = unencrypted;
	personalData = new PersonalData();
}

//Hide the data within the binary and return it all
string Algorithm::hide() {
	size_t location = 0;

	//Char pointer creator
	std::string binaryPointer = (personalData->address + '@').c_str();
	//@ indicates end of a thing of info


	int place = static_cast<int>((((systime % 10) + 1) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	//Rudimentary algorithm
	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->birthday + '@').c_str();

	place = static_cast<int>((((systime % 10) + 2) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->gender + '@').c_str();

	place = static_cast<int>((((systime % 10) + 3) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->first_name + '@').c_str();

	place = static_cast<int>((((systime % 10) + 4) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->last_name + '@').c_str();

	place = static_cast<int>((((systime % 10) + 5) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->med_history + '@').c_str();

	place = static_cast<int>((((systime % 10) + 6) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->pcp + '@').c_str();

	place = static_cast<int>((((systime % 10) + 7) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->social_security + '@').c_str();

	place = static_cast<int>((((systime % 10) + 8) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);


	//This should go at the end or things get messy
	binaryPointer = (to_string(systime) + '@' + to_string(dataSize) + '@').c_str();

	binaryData.insert(location, binaryPointer);

	return binaryData;
}

//Discover the data within the binary, assign it to the variables so they may be called with getter methods
void Algorithm::find() {
	std::string systimeString = "";
	std::string dataSizeString = "";

	size_t location = 0;

	while (binaryData.at(location) != '@') {
		systimeString += binaryData.at(location);
		binaryData.erase(location,1);
	}
	binaryData.erase(location,1);

	if (binaryData.at(location) == NULL) {
		throw("Improperly formatted or no data");
	}

	systime = std::stoll(systimeString);

	while (binaryData.at(location) != '@') {
		dataSizeString += binaryData.at(location);
		binaryData.erase(location,1);
	}
	binaryData.erase(location,1);

	if (binaryData.at(location) == NULL) {
		throw("Improperly formatted or no data");
	}

	dataSize = std::stoll(dataSizeString);

	int place = static_cast<int>(((systime % 10) + 8 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@') {
		personalData->social_security += binaryData.at(location + place);
		binaryData.erase(location + place,1);
	}
	binaryData.erase(location + place,1);

	place = static_cast<int>(((systime % 10) + 7 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@') {
		personalData->pcp += binaryData.at(location + place);
		binaryData.erase(location + place,1);
	}
	binaryData.erase(location + place,1);

	place = static_cast<int>(((systime % 10) + 6 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@') {
		personalData->med_history += binaryData.at(location + place);
		binaryData.erase(location + place,1);
	}
	binaryData.erase(location + place,1);

	place = static_cast<int>(((systime % 10) + 5 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@') {
		personalData->last_name += binaryData.at(location + place);
		binaryData.erase(location + place,1);
	}
	binaryData.erase(location + place,1);

	place = static_cast<int>(((systime % 10) + 4 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@') {
		personalData->first_name += binaryData.at(location + place);
		binaryData.erase(location + place,1);
	}
	binaryData.erase(location + place,1);

	place = static_cast<int>(((systime % 10) + 3 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@') {
		personalData->gender += binaryData.at(location + place);
		binaryData.erase(location + place,1);
	}
	binaryData.erase(location + place, 1);

	place = static_cast<int>(((systime % 10) + 2 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@') {
		personalData->birthday += binaryData.at(location + place);
		binaryData.erase(location + place,1);
	}
	binaryData.erase(location + place,1);

	place = static_cast<int>(((systime % 10) + 1 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@') {
		personalData->address += binaryData.at(location + place);
		binaryData.erase(location + place,1);
	}
	binaryData.erase(location + place,1);

}

//Return the personal data
PersonalData* Algorithm::getPD() {
	PersonalData *pdp = personalData;

	return pdp;
}

//Return the binary data that originally hid the personal data
std::string Algorithm::getBinary() {
	return binaryData;
}
