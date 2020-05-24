/*
 * XorShift.h
 *
 *  Created on: Apr 6, 2015
 *      Author: michael
 */

#ifndef XORSHIFT_H_
#define XORSHIFT_H_

#include <exception>
#include "stdint.h"

//inspired by
// http://www.javamex.com/tutorials/random_numbers/xorshift.shtml
//and fi.jyu.miselico.bigdata.task3.XorShift

class XorShift {
	private:
		uint_fast64_t state;
	public:
		XorShift(uint_fast64_t seed) :
				state(seed) {
			if (seed == 0) {
				throw std::exception();
			}
		}

		inline uint_fast64_t randomLong() {
			uint_fast64_t x;
			x = this->state;
			x ^= (x << 21);
			x ^= (x >> 35);
			x ^= (x << 4);
			this->state = x;
			return x;
		}

	};

#endif /* XORSHIFT_H_ */
