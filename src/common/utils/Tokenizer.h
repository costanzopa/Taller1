/*
 * Tokenizer.h
 *
 *  Created on: Sep 4, 2016
 *      Author: mario
 */

#ifndef COMMON_UTILLS_TOKENIZER_H_
#define COMMON_UTILLS_TOKENIZER_H_

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Tokenizer {
public:
	Tokenizer();
	virtual ~Tokenizer();

	vector<string> tokenize(string &toSpli, char cut);
};

#endif /* COMMON_UTILLS_TOKENIZER_H_ */
