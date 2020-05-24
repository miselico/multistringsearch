/*
 * ExactMatcher.h
 *
 *  Created on: Apr 5, 2015
 *      Author: michael
 */

#ifndef EXACTMATCHER2_H_
#define EXACTMATCHER2_H_

#include <ctype.h>
#include <vector>
#include <stdint.h>

namespace exactMatcher2 {

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
	virtual ~ExactMatcher();
	bool contains(uint8_t * start);
private:
	Patricia::Node * root;
	ExactMatcher(Patricia::Node * r) : root(r){};
};

class Builder {
public:
	//Builder();
	Builder * add(uint8_t * patternStart);
	ExactMatcher build();
private:
	std::vector<uint8_t *> patterns;
};

}
#endif /* EXACTMATCHER2_H_ */
