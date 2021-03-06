/*
 * StringDistance.h
 *
 *  Created on: 22 de mar de 2017
 *      Author: mafra
 */

#ifndef STRINGDISTANCE_H_
#define STRINGDISTANCE_H_

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>

namespace stringdistance {

class StringDistance {

protected:
	std::string s1, s2;
	std::vector<std::string> s1Tokens, s2Tokens;

public:
	StringDistance(std::string s1, std::string s2);
	virtual ~StringDistance();
	virtual double distance(void) = 0;
};

} /* namespace stringdistance */

#endif /* STRINGDISTANCE_H_ */
