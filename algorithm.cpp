/*
* This file reads in a binary input or converts sent info to binary then randomly hides provided data inside the binary
* author: Kayvan Ehteshami
*
*/

#include "stdafx.h"
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
	varNumb = 7;
}

//Constructor to accept binary data alongside personal data
Algorithm::Algorithm(std::string binary, PersonalData *pd) {
	//Set up time and other variables
	__int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	systime = now;
	varNumb = 7;
	dataSize = sizeof(binary);

	personalData = pd;

	//Binary.size() returns unsigned
	for (unsigned i = 0; i < binary.size(); i++) {
		binaryData = binary;
	}

}

//Hide the data within the binary and return it all
string Algorithm::hide() {
	size_t location = 0;

	//Char pointer creator
	std::string binaryPointer = (to_string(systime) + '@' + to_string(dataSize) + '@').c_str();
	//@ indicates end of a thing of info
	
	while (!binaryPointer.empty()) {
		binaryData.insert(location, binaryPointer);
	}

	binaryPointer = (personalData->address + '@').c_str();

    int place = static_cast<int>((((systime % 10) + 1) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	//Rudimentary algorithm
	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->birthday + '@').c_str();

	place = static_cast<int>((((systime % 10) + 2) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->first_name + '@').c_str();

	place = static_cast<int>((((systime % 10) + 3) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->last_name + '@').c_str();

	place = static_cast<int>((((systime % 10) + 4) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->med_history + '@').c_str();

	place = static_cast<int>((((systime % 10) + 5) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->pcp + '@').c_str();

	place = static_cast<int>((((systime % 10) + 6) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);

	binaryPointer = (personalData->social_security + '@').c_str();

	place = static_cast<int>((((systime % 10) + 7) * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 5)));

	binaryData.insert(location + place, binaryPointer);


	return binaryData;
}

//Discover the data within the binary, assign it to the variables so they may be called with getter methods
void Algorithm::find() {
	std::string systimeString = "";
	std::string dataSizeString = "";

	size_t location = 0;

	while (binaryData.at(location) != '@' || binaryData.at(location) != NULL) {
		systimeString += binaryData.at(location);
		binaryData.erase(location);
	}
	binaryData.erase(location);

	if (binaryData.at(location) == NULL) {
		throw("Improperly formatted or no data");
	}

	systime = std::stoll(systimeString);

	while (binaryData.at(location) != '@' || binaryData.at(location) != NULL) {
		dataSizeString += binaryData.at(location);
		binaryData.erase(location);
	}
	binaryData.erase(binaryData.begin());

	if (binaryData.at(location) == NULL) {
		throw("Improperly formatted or no data");
	}

	dataSize = std::stoll(dataSizeString);

	int place = static_cast<int>(((systime % 10) + 7 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@' || binaryData.at(location + place) != NULL) {
		personalData->social_security += binaryData.at(location + place);
		binaryData.erase(location + place);
	}
	binaryData.erase(location + place);
	
	place = static_cast<int>(((systime % 10) + 6 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@' || binaryData.at(location + place) != NULL) {
		personalData->pcp += binaryData.at(location + place);
		binaryData.erase(location + place);
	}
	binaryData.erase(location + place);

	place = static_cast<int>(((systime % 10) + 5 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@' || binaryData.at(location + place) != NULL) {
		personalData->med_history += binaryData.at(location + place);
		binaryData.erase(location + place);
	}
	binaryData.erase(location + place);

	place = static_cast<int>(((systime % 10) + 4 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@' || binaryData.at(location + place) != NULL) {
		personalData->last_name += binaryData.at(location + place);
		binaryData.erase(location + place);
	}
	binaryData.erase(location + place);

	place = static_cast<int>(((systime % 10) + 3 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@' || binaryData.at(location + place) != NULL) {
		personalData->first_name += binaryData.at(location + place);
		binaryData.erase(location + place);
	}
	binaryData.erase(location + place);

	place = static_cast<int>(((systime % 10) + 2 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@' || binaryData.at(location + place) != NULL) {
		personalData->birthday += binaryData.at(location + place);
		binaryData.erase(location + place);
	}
	binaryData.erase(location + place);

	place = static_cast<int>(((systime % 10) + 1 * (systime % 33)) / 2 + (dataSize / ((systime % 3) + 1)));
	while (binaryData.at(location + place) != '@' || binaryData.at(location + place) != NULL) {
		personalData->address += binaryData.at(location + place);
		binaryData.erase(location + place);
	}
	binaryData.erase(location + place);

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
