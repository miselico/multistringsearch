/*
 * TwoCharCheck.cpp
 *
 *  Created on: Apr 9, 2015
 *      Author: michael
 */

#include "TwoCharCheck.h"
#include <fstream>

FastCheck::TwoCharCheck::TwoCharCheck() {
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			this->masks[i][j] = 0;
		}
	}
}

void FastCheck::TwoCharCheck::add(uint8_t c1, uint8_t c2, uint_fast8_t positionc1) {
	this->masks[c1][c2] |= (1 << positionc1);
}

void FastCheck::TwoCharCheck6_7::add(uint8_t* pattern) {
	// a little loop unrolling:
	uint8_t c1 = *(pattern + 0);
	uint8_t c2 = *(pattern + 1);
	this->TwoCharCheck::add(c1, c2, 1);
	c1 = *(pattern + 2);
	this->TwoCharCheck::add(c2, c1, 2);
	c2 = *(pattern + 3);
	this->TwoCharCheck::add(c1, c2, 3);
	c1 = *(pattern + 4);
	this->TwoCharCheck::add(c2, c1, 4);
	c2 = *(pattern + 5);
	this->TwoCharCheck::add(c1, c2, 5);
	c1 = *(pattern + 6);
	this->TwoCharCheck::add(c2, c1, 6);
	c2 = *(pattern + 7);
	this->TwoCharCheck::add(c1, c2, 7);
}

FastCheck::TwoCharCheck6_7 FastCheck::TCC6_7FromFile(std::string filename) {
	//stackoverflow 18816126
	std::ifstream file(filename, std::ios::binary);
	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	//std::vector<char> buffer(size);
	char* memory = (char *) malloc(size * sizeof(char));
	if (!(file.read(memory, size))) {
		throw std::exception();
	}
	uint8_t* addr = (uint8_t*) memory;
	unsigned int patterns = size / (sizeof(uint8_t) * 8);

	FastCheck::TwoCharCheck6_7 c;

	uint8_t * patternStart = addr;
	for (unsigned int i = 0; i < patterns; i += 1) {
		patternStart += 8;
		c.add(addr + i);
	}
	return c;
}
