//============================================================================
// Name        : mutisearch.cpp
// Author      : Michael Cochez
// Version     :
// Copyright   : All rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>


#include <functional>
#include <string>

#include "rabinhash.h"
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <time.h>
#include <stdint.h>

using namespace std;
using namespace rabin;
using namespace boost::interprocess;

int rabinHashTest() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	RabinHash hashFunc;
	for (uint32_t i = 0; i < 256 * 256; i++) {
		uint32_t * pi = &i;
		uint8_t * v = (uint8_t *) (pi);
		//iterate 'backward - endianness'
		for (int j = 3; j >= 0; j--) {
			hashFunc.push(v + j);
		}
		cout << hashFunc.fingerprint << endl;
		//cout << int(i) << endl;
	}
	return 0;
}

int rabinLargeFile() {
	clock_t startTime = clock();

	// Create the file mapping
	file_mapping fm("/home/michael/Documents/ubuntu-14.04-desktop-amd64.iso",
			read_only);
	// Map the file in memory
	mapped_region region(fm, read_only);
	// Get the address where the file has been mapped
	uint8_t * addr = (uint8_t *) region.get_address();
	std::size_t elements = region.get_size() / sizeof(uint8_t);

	RabinHash h;

	for (uint i = 0; i < elements; i++) {
		h.push(addr + i);
	}

	cout << h.fingerprint << endl;
	cout << double(clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds."
			<< endl;
	return 0;
}

int testHash() {
	char nts1[] = "Test";
	  char nts2[] = "Test";
	  std::string str1 (nts1);
	  std::string str2 (nts2);

	  std::hash<char*> ptr_hash;
	  std::hash<std::string> str_hash;

	  std::cout << "same hashes:\n" << std::boolalpha;
	  std::cout << "nts1 and nts2: " << (ptr_hash(nts1)==ptr_hash(nts2)) << '\n';
	  std::cout << "str1 and str2: " << (str_hash(str1)==str_hash(str2)) << '\n';

	return 0;
}

int main(int argc, char **argv) {
// return rabinLargeFile();
	return testHash();
}

