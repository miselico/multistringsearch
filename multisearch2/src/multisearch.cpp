//============================================================================
// Name        : mutisearch.cpp
// Author      : Michael Cochez
// Version     :
// Copyright   : All rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <bitset>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ExactMatcher.h"
#include "FastCheck.h"
#include "rabinhash.h"
#include "SingleCharCheck.h"
#include "TwoCharCheck.h"

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

int testHash() {
	char nts1[] = "Test";
	char nts2[] = "Test";
	std::string str1(nts1);
	std::string str2(nts2);

//	std::

	std::hash<char*> ptr_hash;
	std::hash<std::string> str_hash;

	std::cout << "same hashes:\n" << std::boolalpha;
	std::cout << "nts1 and nts2: " << (ptr_hash(nts1) == ptr_hash(nts2)) << '\n';
	std::cout << "str1 and str2: " << (str_hash(str1) == str_hash(str2)) << '\n';

	return 0;
}

bool exactMatchTest(std::vector<uint8_t*> p1, std::vector<uint8_t *> p2, std::vector<bool> truth) {
	exactMatcher::Builder b;
	for (std::vector<uint8_t *>::iterator p = p1.begin(); p != p1.end(); p++) {
		b.add(*p);
	}
	exactMatcher::ExactMatcher m = b.build();
	for (unsigned int i = 0; i < p2.size(); i++) {
		uint8_t* p = p2[i];
		bool result = m.contains(p);
		if (result != truth[i]) {
			return false;
		}
	}
	return true;
}

void exactMatchAllTest() {

	for (int i = 0; i <= 4; ++i) {
		vector<uint8_t *> p1;
		vector<uint8_t *> p2;
		vector<bool> t;
		switch (i) {
		uint8_t* data;
		uint8_t* data2;
	case 0:
		data2 = (uint8_t*) ("pattern1");
		p2.push_back(data2);
		t.push_back(false);
		break;
	case 1:
		data = (uint8_t*) ("pattern1");
		p1.push_back(data);
		data2 = (uint8_t*) ("pattern1");
		p2.push_back(data2);
		t.push_back(true);
		break;
	case 2:
		data = (uint8_t*) ("pattern1");
		p1.push_back(data);
		data2 = (uint8_t*) ("pattern0");
		p2.push_back(data2);
		t.push_back(false);
		break;
	case 3:
		data = (uint8_t*) ("pattern1\npattern2");
		for (int i = 0; i < 2; i++) {
			uint8_t* d = data + (i * 9);
			p1.push_back(d);
		}
		data2 = (uint8_t*) ("pattern1\npattern2\n");
		for (int i = 0; i < 2; i++) {
			uint8_t* d = data2 + (i * 9);
			p2.push_back(d);
		}
		t.push_back(true);
		t.push_back(true);
		break;
	case 4:
		data = (uint8_t*) ("pattern1\npattern2\npattern3\n");
		for (int i = 0; i < 3; i++) {
			uint8_t* d = data + (i * 9);
			p1.push_back(d);
		}
		data2 = (uint8_t*) ("pattern1\npatternZ\npattern3\n");
		for (int i = 0; i < 3; i++) {
			uint8_t* d = data2 + (i * 9);
			p2.push_back(d);
		}
		t.push_back(true);
		t.push_back(false);
		t.push_back(true);
		break;
	default:
		break;
		}
		cout << exactMatchTest(p1, p2, t) << endl;
	}
}

void ExectMatchTest() {
	uint8_t* data = (uint8_t*) ("pattern1\npattern2\npattern3\n");
	uint8_t* data2 = (uint8_t*) ("pattern1\npatternZ\npattern3\n");
	exactMatcher::Builder b;
	for (int i = 0; i < 3; i++) {
		uint8_t* d = data + (i * 9);
		b.add(d);
	}
	exactMatcher::ExactMatcher m = b.build();
	for (int i = 0; i < 3; i++) {
		uint8_t* d = data2 + (i * 9);
		cout << m.contains(d) << endl;
	}
}

void baseline1() {
	clock_t startTime = clock();

	// Create the file mapping
	file_mapping fm("/home/michael/Documents/ubuntu-14.04-desktop-amd64.iso", read_only);
	// Map the file in memory
	mapped_region region(fm, read_only);
	// Get the address where the file has been mapped
	uint8_t * addr = (uint8_t *) region.get_address();
	std::size_t elements = region.get_size() / sizeof(uint8_t);

	uint_fast8_t accum = 0;
	for (uint i = 0; i < elements; i++) {
		accum ^= *(addr + i);
	}

	cout << accum << endl;
	cout << double(clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;
}

void baseline2() {

	exactMatcher::Builder b;
	uint8_t* data = (uint8_t*) ("ubuntu14\nubuntuds\ndeskopam\namd64ubu");
	for (int i = 0; i < 4; i++) {
		uint8_t* d = data + (i * 9);
		b.add(d);
	}
	exactMatcher::ExactMatcher m = b.build();

	clock_t startTime = clock();

	// Create the file mapping
	file_mapping fm("/home/michael/Documents/ubuntu-14.04-desktop-amd64.iso", read_only);
	// Map the file in memory
	mapped_region region(fm, read_only);
	// Get the address where the file has been mapped
	uint8_t * addr = (uint8_t *) region.get_address();
	std::size_t elements = region.get_size() / sizeof(uint8_t);

	uint_fast8_t accum = 0;
	for (uint i = 0; i < elements; i++) {
		accum ^= m.contains(addr + i);
	}

	cout << accum << endl;
	cout << double(clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;
}

int baseline3() {
	clock_t startTime = clock();

	// Create the file mapping
	file_mapping fm("/home/michael/Documents/ubuntu-14.04-desktop-amd64.iso", read_only);
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
	cout << double(clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;
	return 0;
}

void baseline1b() {
	clock_t startTime = clock();

	// Create the file mapping
	file_mapping fm("/home/michael/Documents/multistringsearch/RandomData.dat", read_only);
	// Map the file in memory
	mapped_region region(fm, read_only);
	// Get the address where the file has been mapped
	uint8_t * addr = (uint8_t *) region.get_address();
	std::size_t elements = region.get_size() / sizeof(uint8_t);

	uint_fast8_t accum = 0;
	for (uint i = 0; i < elements; i++) {
		accum ^= *(addr + i);
	}

	cout << accum << endl;
	cout << double(clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;
}

void baseline2b(std::string patterns, std::string data) {
	exactMatcher::ExactMatcher m = exactMatcher::readFromFile(patterns);
	clock_t startTime = clock();

	// Create the file mapping
	file_mapping fm(data.c_str(), read_only);
	// Map the file in memory
	mapped_region region(fm, read_only);
	// Get the address where the file has been mapped
	uint8_t * addr = (uint8_t *) region.get_address();
	std::size_t elements = region.get_size() / sizeof(uint8_t);

	int accum = 0;
	for (uint i = 0; i < elements; i++) {
		if (m.contains(addr + i)) {
			accum++;
		}
		if (i % 10000000 == 0) {
			cout << "step " << i << endl;
		}
	}

	cout << accum << endl;
	cout << double(clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;
}

int baseline3b() {
	clock_t startTime = clock();

	// Create the file mapping
	file_mapping fm("/home/michael/Documents/multistringsearch/RandomData.dat", read_only);
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
	cout << double(clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;
	return 0;
}

void singleCharCheckBaseline(std::string patterns, std::string data) {
	exactMatcher::ExactMatcher m = exactMatcher::readFromFile(patterns);
	FastCheck::SingleCharCheck7 SCC7 = *FastCheck::SCC7FromFile(patterns);

	clock_t startTime = clock();

	// Create the file mapping
	file_mapping fm(data.c_str(), read_only);
	// Map the file in memory
	mapped_region region(fm, read_only);
	// Get the address where the file has been mapped
	uint8_t * addr = (uint8_t *) region.get_address();
	std::size_t elements = region.get_size() / sizeof(uint8_t);

	//number of matches
	int accum = 0;
	//number of checks saved
	int saved = 0;
	for (uint i = 7; i < elements; i += 8) {
		FastCheck::SingleCheckMask mask = SCC7.check(*(addr + i));
		for (uint j = 0; j < 8; j++) {
			//j-th bit in mask is one
			if (mask.test(j)) {
				if (m.contains(addr + (i - j))) {
					accum++;
				}
			} else {
				saved++;
			}
		}
		if (i % (7 + (8 * 1000000)) == 0) {
			cout << "step " << i << endl;
		}
	}

	cout << "matches" << accum << endl;
	cout << "saved evaluations" << saved << endl;
	cout << double(clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;

}

//check character 6 and 7 and decide
void twoCharCheckBaseLine(std::string patterns, std::string data) {
	exactMatcher::ExactMatcher m = exactMatcher::readFromFile(patterns);
	FastCheck::TwoCharCheck6_7 SCC7 = FastCheck::TCC6_7FromFile(patterns);

	clock_t startTime = clock();

	// Create the file mapping
	file_mapping fm(data.c_str(), read_only);
	// Map the file in memory
	mapped_region region(fm, read_only);
	// Get the address where the file has been mapped
	uint8_t * addr = (uint8_t *) region.get_address();
	std::size_t elements = region.get_size() / sizeof(uint8_t);

	//number of matches
	int accum = 0;
	//number of checks saved
	int saved = 0;
	for (uint i = 6; i < elements; i += 8) {
		FastCheck::Mask mask = SCC7.check(*(addr + i), *(addr + i + 1));
		for (uint j = 1; j < 8; j++) { //the 0 th bit cannot be set.
			//j-th bit in mask is one
			if (mask.test(j)) {
				if (m.contains(addr + (i - j + 1))) {
					accum++;
				}
			} else {
				saved++;
			}
		}
		//there is no check starting from pos. 7 done yet.
		if (m.contains(addr + i + 1)) {
			accum++;
		}

		if (i % (7 + (8 * 1000000)) == 0) {
			cout << "step " << i << endl;
		}
	}

	cout << "matches" << accum << endl;
	cout << "saved evaluations" << saved << endl;
	cout << double(clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;
}

void bruteForceSearch(std::string patternsFileName, std::string data) {
	std::ifstream file(patternsFileName, std::ios::binary);
	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	char* memory = (char *) malloc(size * sizeof(char));
	if (!(file.read(memory, size))) {
		throw std::exception();
	}
	char* addr = (char*) memory;
	unsigned int patternsCount = size / (sizeof(char) * 8);

	cout << patternsCount << endl;

	std::set<std::string> patterns;
	//patterns.max_load_factor(0.5);

	char* patternStart = addr;
	for (unsigned int i = 0; i < patternsCount; i += 1) {
		patternStart += 8;
		std::string  s(patternStart, 8);
		cout << s << endl;
		patterns.insert(s);
	}

	cout << "patterns size " << patterns.size() << endl;



	free (memory);

	cout << "Brute force is not implemented completely." << endl;

	return;

	clock_t startTime = clock();
	// Create the file mapping
	file_mapping fm(data.c_str(), read_only);
	// Map the file in memory
	mapped_region region(fm, read_only);
	// Get the address where the file has been mapped
	char * dataaddr = (char *) region.get_address();
	std::size_t elements = region.get_size() / sizeof(char);

	int accum = 0;
	for (uint i = 0; i < elements; i++) {
		if (patterns.count(std::string(dataaddr + i)) == 1) {
			accum++;
		}
		if (i % 100 == 0){
			cout << "step " << i  << '/' << elements << "=" << double(i)/elements << endl;
			cout << double(clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;
		}
	}

	cout << accum << endl;
	cout << double(clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;

}


int main(int argc, char **argv) {
	//return rabinLargeFile();
	//return testHash();
	//exactMatchAllTest();
	//baseline1();
	//baseline2();

		//testHash();

	//bruteForceSearch("/home/michael/Documents/multistringsearch/RandomPatterns.dat", "/home/michael/Documents/multistringsearch/RandomData.dat");
	cerr << "A few pieces have to be corrected. the reading of patterns was limited to amount/8" << endl;
	if (argc != 3){
		throw "Not enough args" ; //new exception();
	}
	//bruteForceSearch(argv[1], argv[2]);
	baseline2b(argv[1], argv[2]);
	//singleCharCheckBaseline(argv[1], argv[2]);
	//twoCharCheckBaseLine(argv[1], argv[2]);

	cout << "Blab";
	return 0;
}

