#include "pch.h"
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
	pd->last_name = "Doe";
	pd->med_history = "Death, lyme disease, glutten allergy";
	pd->pcp = "Dr. Mantis Tobagin";
	pd->social_security = "555-55-5555";

	std::string binary = "01010101010111111111111111000010101010100000";

	Algorithm algie(binary, pd);
}
