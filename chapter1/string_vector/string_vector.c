/*
 * string_vector.c
 *
 *  Created on: 13 de mar de 2017
 *      Author: mafra
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "string_vector.h"

/*
 * Allocates a new StringVector
 */
StringVector string_vector_create(unsigned initialSize) {

	StringVector strVec = (StringVector) malloc(sizeof(StringVector));
	if (strVec == NULL) {
		fprintf(stderr, "Error allocating array of size %d: %s\n", initialSize,
				strerror(errno));
		return NULL;
	}

	strVec->numElements = 0;
	strVec->size = initialSize;
	strVec->vector = (char**) calloc(sizeof(char*), initialSize);

	return strVec;
}

/*
 * Adds a new string to the vector
 */
int string_vector_add(StringVector strVec, char *string) {

	if (string == NULL) {
		fprintf(stderr, "Trying to add NULL string to StringVector\n");
		return EXIT_FAILURE;
	}

	if (strVec == NULL) {
		fprintf(stderr, "NULL StringVector trying to add new string\n");
		return EXIT_FAILURE;
	}

	if (strVec->numElements >= strVec->size) {
		fprintf(stderr, "StringVector is full\n");
		return EXIT_FAILURE;
	}

	char *newString = (char*) malloc(strlen(string) + 1);
	strcpy(newString, string);
	strVec->vector[strVec->numElements] = newString;
	strVec->numElements++;

	return EXIT_SUCCESS;
}

/**
 * Gets the string at position
 */
char *
string_vector_get(StringVector strVec, unsigned position) {

	if (strVec == NULL) {
		fprintf(stderr, "NULL StringVector in function string_vector_get\n");
		return NULL;
	}

	if (position > strVec->numElements) {
		fprintf(stderr, "Position out of bounds: %d (%d elements)\n", position,
				strVec->numElements);
		return NULL;
	}

	return strVec->vector[position];
}

/**
 * Swaps the elements in two positions
 */
int string_vector_swap(StringVector strVec, unsigned position1,
		unsigned position2) {

	if (strVec == NULL) {
		fprintf(stderr, "NULL StringVector in string_vector_swap\n");
		return EXIT_FAILURE;
	}

	if (position1 >= strVec->numElements) {
		fprintf(stderr,
				"Invalid position 1 argument in string_vector_swap: %d (%d elements)\n",
				position1, strVec->numElements);
		return EXIT_FAILURE;
	}

	if (position2 >= strVec->numElements) {
		fprintf(stderr,
				"Invalid position 2 argument in string_vector_swap: %d (%d elements)\n",
				position2, strVec->numElements);
		return EXIT_FAILURE;
	}

	char *element1 = string_vector_get(strVec, position1);
	char *element2 = string_vector_get(strVec, position2);
	strVec->vector[position1] = element2;
	strVec->vector[position2] = element1;

	return EXIT_SUCCESS;
}

/**
 * Frees all memory allocated by the StringVector
 */
void string_vector_free(StringVector strVec) {

	if (strVec == NULL) {
		fprintf(stderr, "NULL StringVector passed in freeStringVector\n");
		return;
	}

	for (unsigned i = 0; i < strVec->numElements; i++) {
		free(strVec->vector[i]);
	}

	free(strVec->vector);
	free(strVec);
}
