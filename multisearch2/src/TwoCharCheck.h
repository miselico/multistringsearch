/*
 * TwoCharCheck.h
 *
 *  Created on: Apr 9, 2015
 *      Author: michael
 */

#ifndef TWOCHARCHECK_H_
#define TWOCHARCHECK_H_

#include <stdint.h>
#include <bitset>
#include "FastCheck.h"


namespace FastCheck {

class TwoCharCheck {
public:
	TwoCharCheck();
	virtual ~TwoCharCheck(){};
	inline Mask check(uint8_t c1, uint8_t c2){
			return this->masks[c1][c2];
	}
protected:
	void add (uint8_t c1, uint8_t c2, uint_fast8_t positionc1);
private:
	Mask masks[256][256];
};


class TwoCharCheck6_7 : public TwoCharCheck{
public:
	using TwoCharCheck::check;
	void add(uint8_t * pattern);
};


TwoCharCheck6_7 TCC6_7FromFile(std::string filename);









}

#endif /* TWOCHARCHECK_H_ */
