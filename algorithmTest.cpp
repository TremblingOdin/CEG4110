#include "algorithm.h"

using namespace std;

class AlgorithmTest() {
	std::string pd[] = ["Jane", "Doe", "4/7/1776", "420696969", "123 Fake Street", "Dr. Acula", "Hemochromatosis, Gaut, Alzheimers' Disorder, Glass Bones Disorder, Paper Skin Disorder, Addicted to Mr. Brightside, Tumblrculosis, Candidiasis Hypersensitivity, Radiiluciussensibilitatem, Situational Depression, Situational Mania, Gluten Allergy"];
	
	char binary[] = ['1','0','1','0','1','1','0','0','1','1','1'];	

	Algorithm algor = new Algorithm(pd, binary);
	
	void main() {
		std::cout << algor.getPD();
		return 0;
	}
}
