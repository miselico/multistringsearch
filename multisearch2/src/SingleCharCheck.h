/*
 * SingleCharCheck.h
 *
 *  Created on: Apr 9, 2015
 *      Author: michael
 */

#ifndef SINGLECHARCHECK_H_
#define SINGLECHARCHECK_H_

#include <stdint.h>
#include <bitset>
#include <fstream>
#include "FastCheck.h"

namespace FastCheck {

class SingleCharCheck{
public:
	SingleCharCheck();
	virtual ~SingleCharCheck(){};
	SingleCheckMask check(uint8_t c);
protected:
	void add(uint8_t character, uint_fast8_t position );
private:
	SingleCheckMask masks[256];
};


class SingleCharCheck7 : public SingleCharCheck{
public:
	using SingleCharCheck::check;
	void add(uint8_t * pattern);
};

class SingleCharCheck8 : public SingleCharCheck{
public:
	SingleCharCheck8();
	using SingleCharCheck::check;
	void add(uint8_t * pattern);
};

SingleCharCheck7 * SCC7FromFile(std::string filename);

}
#endif /* SINGLECHARCHECK_H_ */
