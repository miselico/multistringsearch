//============================================================================
// Name        : GenerateData.cpp
// Author      : Michael Cochez
// Version     :
// Copyright   : All rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include "XorShift.h"
#include "stdint.h"
//#include <string>

using namespace std;

const uint_fast64_t standardSeed = 4678646574653L;

const uint_fast64_t standardAmount = 1024 * 1024 * 1024; //1Gb

const double thresholdPercent = 0.20;//was 0.20

const uint_fast64_t threshold = uint_fast64_t(thresholdPercent  * (double(UINT_FAST64_MAX)));

char generateOne(std::vector<char> & chars, XorShift & shifter) {
	for (std::vector<char>::iterator iter = chars.begin(); iter != chars.end(); iter++) {
		uint_fast64_t val = shifter.randomLong();
		if (val < threshold) {
			return *iter;
		}
	}
	return chars.back();
}

int main(int argc, char **argv) {
	std::vector<char> chars;
	for (char i = 'a'; i <= 'z'; i++) {
		chars.push_back(i);
	}
	for (char i = 'A'; i <= 'Z'; i++) {
		chars.push_back(i);
	}
	uint_fast64_t seed = standardSeed;
	uint_fast64_t amount = standardAmount;

	if (argc == 2){
		seed = 786889946545L;
		amount = 8 * 100000;
	}

	XorShift shifter(seed);

	//cout << threshold << endl;
	//cout << double(UINT_FAST64_MAX) << endl;
	for (uint_fast64_t i = 0; i < amount; i++) {
		std::cout << generateOne(chars, shifter);
	}
	return 0;
}



