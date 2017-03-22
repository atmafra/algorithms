/*
 * Levenshtein.h
 *
 *  Created on: 22 de mar de 2017
 *      Author: mafra
 */

#ifndef LEVENSHTEIN_H_
#define LEVENSHTEIN_H_

#include "StringDistance.h"

namespace stringdistance {

class Levenshtein: public StringDistance {
public:
	Levenshtein(std::string s1, std::string s2);
	double distance(void);
	~Levenshtein();
};

} /* namespace stringdistance */

#endif /* LEVENSHTEIN_H_ */
