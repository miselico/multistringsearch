/*
 * rabinhash.h
 *
 *  Created on: Apr 5, 2015
 *      Author: michael
 */

#ifndef RABINHASH_H_
#define RABINHASH_H_

#include <stdint.h>
namespace rabin {
class RabinHash {
private:
	//this should become public when romovePostiions are iplemented
	//RabinHash(uint_fast64_t polynome, uint_fast64_t removePositions);
public:
//	RabinHash(uint_fast64_t polynome){
//		RabinHash(polynome, 0);
//	}
	//push 1 char
	//uint_fast64_t push(uint8_t * value);
	//inlining is quite a bit faster.
	/*inline*/ uint_fast64_t push(uint8_t * value){
		int j = this->fingerprint >> RabinHash::shift;
		uint_fast64_t val =  uint_fast64_t (*value);
		this->fingerprint = ((this->fingerprint << 8) | val) ^ RabinHash::pushTable[j];
		return this->fingerprint;
	}

	//push amount chars
	uint_fast64_t push(uint8_t * value, uint_fast32_t amount);
	//push backwards. In nicer C++ one might implemnt this with an iterator
	uint_fast64_t pushBackwards(uint8_t * value, uint_fast8_t amount);

	//Fixed to whatever is in the static push table
	RabinHash();

	uint_fast64_t fingerprint;

private:
	//pushtable for X^12 + X^4 + X^2 + X^1 + 1
	static const uint_fast64_t pushTable[512];
	static const uint_fast8_t shift;

};
}
#endif /* RABINHASH_H_ */