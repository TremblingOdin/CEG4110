#include "algorithm.h"
#include "stdafx.h"
#include <bitset>
#include <ctime>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
	std::vector<std::string> pd = { "Jane", "Doe", "4/7/1776", "420696969", "123 Fake Street", "Dr. Acula", "Hemochromatosis, Gaut, Alzheimers' Disorder, Glass Bones Disorder, Paper Skin Disorder, Addicted to Mr. Brightside, Tumblrculosis, Candidiasis Hypersensitivity, Radiiluciussensibilitatem, Situational Depression, Situational Mania, Gluten Allergy" };
	std::string binary = "01010101010111111111111111000010101010100000";

	Algorithm algie(binary, pd);
}
