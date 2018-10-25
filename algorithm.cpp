/*
 * This file reads in a binary input or converts sent info to binary then randomly hides provided data inside the binary
 * author: Kayvan Ehteshami
 *
 * Mersenne Twister is the basis for the hiding algorithm
 */

#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

class Hider {

	long long systime;
	long long dataSize;
	long long varNumb;

	vector<char> binaryData;
	char personalData [6] [500];

	vector<char> encryptToBinary(char*);

	Hider() {
		time_t tt;
		systime = * localtime(&tt);
		dataSize = 0;
		varNumb = 6;

		personalData = {"","","","","",""};
	}

	Hider(const char binary[], char pD[][]) {
		time_t tt;
		systime = * localtime(&tt);
		varNumb = 6;
		dataSize = sizeof(binary);

		personalData = pD;
		binaryData = binary[];
		
	}

	Hider(const char encryption[], char pD[][]) {
		time_t tt;
		systime = * localtime(&tt);
		varNumb = 6;
		dataSize = sizeof(binary);

		personalData = pD;
		binaryData = encryptToBinary(encryption);
	}
	
	char[] encryptToBinary(char * data) {
		//Small 9 characters buffer
		char output[9];

		//Until the first character pointed by s is not a null character
		while(*data) {
			binaryData.push_back(itoa(*data, output, 
		}
	}
}
