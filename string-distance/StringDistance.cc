/*
 * StringDistance.cc
 *
 *  Created on: 22 de mar de 2017
 *      Author: mafra
 */
#include <sstream>
#include "StringDistance.h"

namespace stringdistance {

StringDistance::StringDistance(std::string s1, std::string s2) {

	this->s1 = s1;
	this->s2 = s2;

	std::istringstream iss(this->s1);

}

StringDistance::~StringDistance() {
	// TODO Auto-generated destructor stub
}

} /* namespace stringdistance */
