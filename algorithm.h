#pragma once
/*
* This file reads in a binary input or converts sent info to binary then randomly hides provided data inside the binary
* author: Kayvan Ehteshami
*
*/

#include <bitset>
#include <ctime>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct PersonalData {
	std::string first_name;
	std::string last_name;
	std::string birthday;
	std::string gender;
	std::string social_security;
	std::string address;
	std::string pcp;
	std::string med_history;
};

class Algorithm {
public:
	//Empty Constructor just incase
	Algorithm();

	//Constructor to accept binary data alongside personal data
	Algorithm(std::string, PersonalData *);

	//Constructor for when just given a nonbinary string
	Algorithm(std::string);

	std::string hide();
	void find();
	PersonalData* getPD();
	std::string getBinary();

	int dataSize;
	int varNumb;

	std::string binaryData;

	//Only accepting First Name, Last Name, Birthday, Social Security, Address, Primary Car Physician, Medical History
	PersonalData *personalData;

private:
	void cleanup();

	void checkFormat(std::string);
	void checkFormat(PersonalData*);
	PersonalData *getFakePD();
};
