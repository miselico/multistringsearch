/*
 * ExactMatcher.h
 *
 *  Created on: Apr 5, 2015
 *      Author: michael
 */

#ifndef EXACTMATCHER_H_
#define EXACTMATCHER_H_

#include <ctype.h>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace exactMatcher {

const int depth = 8;

namespace Patricia {

class Node {
public:
	//Node(){};
	virtual ~Node() {
	}
	;
	virtual bool contains(uint8_t * start, uint_fast8_t count = depth) = 0;
	virtual Node * insert(uint8_t * start, uint_fast8_t count = depth) = 0;
};
}

class ExactMatcher {
	friend class Builder;
public:
	virtual ~ExactMatcher(){
			std::cerr << "Currently some memory is leaked (node strucutre) for the exact matcher" << std::endl;
			free (this->memoryblob);
	}
	bool contains(uint8_t * start);
private:
	void * memoryblob;
	Patricia::Node * root;
	ExactMatcher(Patricia::Node * r) :
			memoryblob(0),root(r) {
	}
	ExactMatcher(Patricia::Node * r, void * memory): memoryblob(memory), root(r) {

	}


};


class Builder {
public:
	//Builder();
	Builder * add(uint8_t * patternStart);
	ExactMatcher build();
	ExactMatcher build(void* memory);
private:
	std::vector<uint8_t *> patterns;
};

ExactMatcher readFromFile(std::string file);

}
#endif /* EXACTMATCHER_H_ */
