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

namespace exactMatcher {
class Builder {
public:
	//Builder();
	Builder * add(uint8_t * patternStart);
	ExactMatcher build();
private:
	std::vector<uint8_t *> patterns;
};

class ExactMatcher {
	friend class Builder;
public:
	virtual ~ExactMatcher();

private:
	ExactMatcher();
};

}
#endif /* EXACTMATCHER_H_ */
