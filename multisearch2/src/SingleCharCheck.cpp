/*
 * SingleCharCheck.cpp
 *
 *  Created on: Apr 9, 2015
 *      Author: michael
 */

#include "SingleCharCheck.h"

#include <iostream>

FastCheck::SingleCharCheck::SingleCharCheck() {
	for (int i = 0; i < 256; i++) {
		this->masks[i] = 0;
	}
}

void FastCheck::SingleCharCheck::add(uint8_t character, uint_fast8_t position) {
	this->masks[character] |= (1 << position);
}

FastCheck::SingleCheckMask FastCheck::SingleCharCheck::check(uint8_t c) {
	return this->masks[c];
}

void FastCheck::SingleCharCheck7::add(uint8_t* pattern) {
	for (uint_fast8_t position = 0; position < 8; position++) {
		uint8_t character = *(pattern + position);
		this->SingleCharCheck::add(character, position);
	}
}

FastCheck::SingleCharCheck8::SingleCharCheck8() {
//should all S bits be set to 1? this check does not tell anything about them
	std::cerr << "It seems like S bits can remain 0. Check this later to make sure";
}

void FastCheck::SingleCharCheck8::add(uint8_t* pattern) {
	for (uint_fast8_t position = 1; position < 8; position++) {
		uint8_t character = *(pattern + position);
		this->SingleCharCheck::add(character, position - 1);
	}
}

FastCheck::SingleCharCheck7 * FastCheck::SCC7FromFile(std::string filename) {
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

	FastCheck::SingleCharCheck7 * c = new FastCheck::SingleCharCheck7();

	uint8_t * patternStart = addr;
	for (unsigned int i = 0; i < patterns; i += 1) {
		patternStart += 8;
		c->add(addr + i);
	}
	return c;
}
