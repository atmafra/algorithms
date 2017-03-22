/*
 * Levenshtein.cc
 *
 *  Created on: 22 de mar de 2017
 *      Author: mafra
 */

#include "Levenshtein.h"

namespace stringdistance {

Levenshtein::Levenshtein(std::string s1, std::string s2)
		: StringDistance(s1, s2) {
}

Levenshtein::~Levenshtein() {
	// TODO Auto-generated destructor stub
}

double Levenshtein::distance(void) {
	return (double) s1.compare(s2);
}

}
/* namespace stringdistance */
