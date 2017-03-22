/*
 * string-distance-test.cpp
 *
 *  Created on: 22 de mar de 2017
 *      Author: mafra
 */
/*
 * teste-string-distance.cpp
 *
 *  Created on: 22 de mar de 2017
 *      Author: mafra
 */
#include <string>
#include <cstdlib>
#include <iostream>
#include "Levenshtein.h"

using namespace stringdistance;

int main(int argc, char* argv[]) {

	if (argc < 3) {
		return EXIT_FAILURE;
	}

	std::string s1, s2;
	s1 = argv[1];
	s2 = argv[2];

	Levenshtein* levenshtein = new Levenshtein(s1, s2);
	double distance = levenshtein->distance();
	std::cout << "Levenshtein distance: " << distance << std::endl;
	delete levenshtein;

	return EXIT_SUCCESS;
}




