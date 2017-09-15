/*
 * Tokenizer.cpp
 *
 *  Created on: Sep 4, 2016
 *      Author: mario
 */

#include "Tokenizer.h"

#include <string>
#include <sstream>
#include <vector>


Tokenizer::Tokenizer() {}

Tokenizer::~Tokenizer() {}

vector<string> Tokenizer::tokenize(string& toSplit, char cut) {
	vector<string> tokens;
	stringstream ss;
	ss.str(toSplit);
	string elem;
	while (getline(ss, elem, cut)) {
		tokens.push_back(elem);
	}
	return tokens;
}
