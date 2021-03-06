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
	dataSize = 0;
	varNumb = 8;
	personalData = getFakePD();
}

//Constructor to accept binary data alongside personal data
Algorithm::Algorithm(std::string binary, PersonalData *pd) {
	//Set up variables
	varNumb = 8;
	
	checkFormat(binary);
	checkFormat(pd);

	while (binary.length() < 500) {
		binary += "~";
	}

	dataSize = binary.length();
	personalData = pd;

	//Binary.size() returns unsigned
	for (unsigned i = 0; i < binary.size(); i++) {
		binaryData = binary;
	}

}

//Constructor for when just given a nonbinary string
Algorithm::Algorithm(std::string unencrypted) {
	if (unencrypted.length() < 500) {
		throw std::invalid_argument("Data must be greater than 500 characters, please check you have not sent corrupted data");
	}
	
	varNumb = 8;
	binaryData = unencrypted;
	personalData = getFakePD();
}

//Hide the data within the binary and return it all
string Algorithm::hide() {
	size_t location = 0;
	size_t end = location + dataSize;

	checkFormat(personalData);

	//Char pointer creator
	std::string binaryPointer = (personalData->address + '@').c_str();
	//@ indicates end of a thing of info


	//Rudimentary algorithm
	binaryData.insert(end, binaryPointer);

	binaryPointer = (personalData->birthday + '@').c_str();

	binaryData.insert(end, binaryPointer);

	binaryPointer = (personalData->gender + '@').c_str();

	binaryData.insert(end, binaryPointer);

	binaryPointer = (personalData->first_name + '@').c_str();

	binaryData.insert(end, binaryPointer);

	binaryPointer = (personalData->last_name + '@').c_str();

	binaryData.insert(end, binaryPointer);

	binaryPointer = (personalData->med_history + '@').c_str();

	binaryData.insert(end, binaryPointer);

	binaryPointer = (personalData->pcp + '@').c_str();

	binaryData.insert(end, binaryPointer);

	binaryPointer = (personalData->social_security + '@').c_str();

	binaryData.insert(end, binaryPointer);


	//This should go at the end or things get messy
	binaryPointer = (to_string(dataSize) + '@').c_str();

	binaryData.insert(location, binaryPointer);

	return binaryData;
}

//Discover the data within the binary, assign it to the variables so they may be called with getter methods
void Algorithm::find() {
	std::string systimeString = "";
	std::string dataSizeString = "";

	size_t location = 0;

	if (binaryData.at(location) == NULL) {
		throw("Improperly formatted or no data");
	}

	while (binaryData.at(location) != '@') {
		dataSizeString += binaryData.at(location);
		binaryData.erase(location,1);
	}
	binaryData.erase(location,1);

	if (binaryData.at(location) == NULL) {
		throw("Improperly formatted or no data");
	}

	dataSize = std::stoll(dataSizeString);
	location = location + dataSize;

	while (binaryData.at(location) != '@') {
		if (binaryData.at(location) != '~') {
			personalData->social_security += binaryData.at(location);
		}
		binaryData.erase(location,1);
	}
	binaryData.erase(location,1);

	while (binaryData.at(location) != '@') {
		if (binaryData.at(location) != '~') {
			personalData->pcp += binaryData.at(location);
		}

		binaryData.erase(location,1);
	}
	binaryData.erase(location,1);

	while (binaryData.at(location) != '@') {
		if (binaryData.at(location) != '~') {
			personalData->med_history += binaryData.at(location);
		}

		binaryData.erase(location,1);
	}
	binaryData.erase(location,1);

	while (binaryData.at(location) != '@') {
		if (binaryData.at(location) != '~') {
			personalData->last_name += binaryData.at(location);
		}

		binaryData.erase(location,1);
	}
	binaryData.erase(location,1);

	while (binaryData.at(location) != '@') {
		if (binaryData.at(location) != '~') {
			personalData->first_name += binaryData.at(location);
		}

		binaryData.erase(location,1);
	}
	binaryData.erase(location,1);

	while (binaryData.at(location) != '@') {
		if (binaryData.at(location) != '~') {
			personalData->gender += binaryData.at(location);
		}

		binaryData.erase(location,1);
	}
	binaryData.erase(location, 1);

	while (binaryData.at(location) != '@') {
		if (binaryData.at(location) != '~') {
			personalData->birthday += binaryData.at(location);
		}

		binaryData.erase(location,1);
	}
	binaryData.erase(location,1);

	while (binaryData.at(location) != '@') {
		if (binaryData.at(location) != '~') {
			personalData->address += binaryData.at(location);
		}

		binaryData.erase(location,1);
	}
	binaryData.erase(location,1);

	cleanup();
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

//Cleans remaining code so there is only binary left, if a character that isn't "~" appears raise error
void Algorithm::cleanup() {
	std::string::iterator cleaner;
	for(cleaner = binaryData.end() - 1; cleaner > binaryData.begin(); cleaner--) {
		if (*cleaner == '~') {
			binaryData.erase(cleaner);
		}
		else if (*cleaner != '0' && *cleaner != '1') {
			throw std::invalid_argument("Improperly formatted, double check if corrupted");
		}
	}
	checkFormat(binaryData);
}

//Checks the format of handed binary string to make sure it's binary
void Algorithm::checkFormat(std::string stringer) {
	std::string::iterator checker;
	
	for(checker = stringer.begin(); checker < stringer.end(); checker++) {
		if (*checker != '1' && *checker != '0') {
			throw std::invalid_argument("Improperly formatted, must be in binary");
		}
	}
}

//Checks format of PersonalData to make sure it doesn't have unwanted special characters and is the right size
void Algorithm::checkFormat(PersonalData* personalData) {
	bool invalidChar = false;
	bool invalidLength = false;

	std::string::iterator checker;

	//'@' is a reserved special character, must not be used
	for(checker = personalData->address.begin(); checker < personalData->address.end(); checker++){
		if (*checker == '@') {
			invalidChar = true;
		}
	}
	
	for (checker = personalData->birthday.begin(); checker < personalData->birthday.end(); checker++) {
		if (*checker == '@') {
			invalidChar = true;
		}
	}

	for (checker = personalData->gender.begin(); checker < personalData->gender.end(); checker++) {
		if (*checker == '@') {
			invalidChar = true;
		}
	}

	for (checker = personalData->first_name.begin(); checker < personalData->first_name.end(); checker++) {
		if (*checker == '@') {
			invalidChar = true;
		}
	}

	for (checker = personalData->last_name.begin(); checker < personalData->last_name.end(); checker++) {
		if (*checker == '@') {
			invalidChar = true;
		}
	}

	for (checker = personalData->med_history.begin(); checker < personalData->med_history.end(); checker++) {
		if (*checker == '@') {
			invalidChar = true;
		}
	}

	for (checker = personalData->pcp.begin(); checker < personalData->pcp.end(); checker++) {
		if (*checker == '@') {
			invalidChar = true;
		}
	}

	for (checker = personalData->social_security.begin(); checker < personalData->social_security.end(); checker++) {
		if (*checker == '@') {
			invalidChar = true;
		}
	}

	//Predefined datasizes
	if (personalData->address.length() > 50 || personalData->gender.length() != 1 || personalData->med_history.length() > 500 || personalData->birthday.length() != 10 ||
		personalData->first_name.length() > 10 || personalData->last_name.length() > 10 || personalData->pcp.length() > 10 || personalData->social_security.length() != 9) {
		invalidLength = true;
	}

	if (personalData->address.length() < 1 || personalData->med_history.length() < 1 || personalData->first_name.length() < 1 || personalData->last_name.length() < 1 ||
		personalData->pcp.length() < 1) {
		invalidLength = true;
	}

	if (invalidChar) {
		throw std::invalid_argument("Improperly formatted, no '@' can be included in Personal Data");
	}
	if (invalidLength) {
		throw std::length_error("Improperly formatted, data size does not fit");
	}
}

//Returns fake PersonalData struct
PersonalData* Algorithm::getFakePD() {
	PersonalData *fpd = new PersonalData();
	fpd->address = "";
	fpd->birthday = "";
	fpd->first_name = "";
	fpd->last_name = "";
	fpd->gender = "";
	fpd->med_history = "";
	fpd->pcp = "";
	fpd->social_security = "";

	return fpd;
}