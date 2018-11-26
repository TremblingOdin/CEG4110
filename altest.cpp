#include "algorithm.h"
#include <bitset>
#include <ctime>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
	PersonalData *pd = new PersonalData();
	pd->address = "1234 fake street";
	pd->birthday = "12/12/1212";
	pd->first_name = "Jane";
	pd->gender = "M";
	pd->last_name = "Doe";
	pd->med_history = "Death, lyme disease, glutten allergy";
	pd->pcp = "Dr. Mantis Tobagin";
	pd->social_security = "555-55-5555";

	std::string binary = "01010101010111111111111111000010101010100000";

	Algorithm algie(binary, pd);

	PersonalData* apd = algie.getPD();

	cout << apd->first_name << " " << apd->last_name << endl
			<< apd->birthday << endl
			<< apd->social_security << endl
			<< apd->address << endl
			<< apd->pcp << endl
			<< apd->med_history << endl;
	
	std::string holder = algie.hide();

	cout << holder << endl;

	Algorithm algor(holder);
	algor.find();

	apd = algor.getPD();

	cout << apd->first_name << " " << apd->last_name << endl
		<< apd->birthday << endl
		<< apd->social_security << endl
		<< apd->address << endl
		<< apd->pcp << endl
		<< apd->med_history << endl;


	delete pd;

	system("pause");
}
