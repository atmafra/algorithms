/*
 * strvec.c
 *
 *  Created on: 13 de mar de 2017
 *      Author: mafra
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <math.h>
#include "string_vector.h"

const unsigned strvec_size_initial_default = __STRVEC_SIZE_INITIAL_DEFAULT_;
const unsigned strvec_size_multiplier_default = __STRVEC_SIZE_MULTIPLIER_DEFAULT_;
const unsigned strvec_size_increments_max_default = __STRVEC_SIZE_INCREMENTS_MAX_DEFAULT_;
const unsigned strvec_size_max = __STRVEC_SIZE_MAX_;

StringVector strvec_create(unsigned initial_size, unsigned size_multiplier, unsigned max_size_increments) {

	StringVector strvec = (StringVector) malloc(sizeof(StringVectorType));

	if (strvec == NULL) {
		fprintf(stderr, "Error allocating string vector: %s\n", strerror(errno));
		return NULL;
	}

	strvec->elements = 0;
	strvec->size = initial_size;
	strvec->size_multiplier = size_multiplier;
	strvec->size_increments_max = max_size_increments;

	unsigned size_max = initial_size * (unsigned) pow(strvec->size_multiplier, strvec->size_increments_max);

	if (size_max > __STRVEC_SIZE_MAX_) {
		fprintf(stderr, "String vector too large: %u elements (maximum is %u)\n", size_max, __STRVEC_SIZE_MAX_);
		free(strvec);
		return NULL;
	}

	strvec->size_max = size_max;
	strvec->vector = (char**) calloc(sizeof(char*), strvec->size);
	return strvec;
}

StringVector strvec_create_default() {
	return strvec_create(strvec_size_initial_default, strvec_size_multiplier_default, strvec_size_increments_max_default);
}

unsigned strvec_new_size(StringVector strvec) {

	if (strvec == NULL) {
		fprintf(stderr, "NULL string vector passed to sting_vector_can_grow()\n");
		return 0;
	}

	unsigned cur_size = strvec->size;
	unsigned new_size = cur_size * strvec->size_multiplier;

	if (new_size > strvec->size_max) {
		return cur_size;
	} else {
		return new_size;
	}
}

bool strvec_can_grow(StringVector strvec) {

	if (strvec == NULL) {
		fprintf(stderr, "NULL string vector passed for strvec_can_grow\n");
		return false;
	}

	if (strvec_new_size(strvec) > strvec->size) {
		return true;
	} else {
		return false;
	}
}

unsigned strvec_grow(StringVector strvec) {

	if (strvec == NULL) {
		fprintf(stderr, "NULL string vector passed to strvec_grow()\n");
		return 0;
	}

	unsigned cur_size = strvec->size;
	unsigned new_size = strvec_new_size(strvec);

	if (new_size <= cur_size) {
		fprintf(stderr, "Cannot grow string vector (maximum size is %u)\n", strvec->size_max);
		return 0;
	}

	strvec->vector = (char**) realloc(strvec->vector, new_size * sizeof(char*));

	if (strvec->vector == NULL) {
		fprintf(stderr, "Error allocating %d bytes to the vector: %s\n", new_size, strerror(errno));
		return 0;
	}

	strvec->size = new_size;
	return new_size - cur_size;
}

char *strvec_get(StringVector strvec, unsigned position) {

	if (strvec == NULL) {
		fprintf(stderr, "NULL StringVector in function strvec_get\n");
		return NULL;
	}

	if (position > strvec->elements) {
		fprintf(stderr, "Position out of bounds: %d (%d elements)\n", position, strvec->elements);
		return NULL;
	}

	return strvec->vector[position];
}

int strvec_set(StringVector strvec, unsigned position, char *string) {

	if (strvec == NULL) {
		fprintf(stderr, "NULL vector passed to strvec_set()\n");
		return EXIT_FAILURE;
	}

	if (position > strvec->elements) {
		fprintf(stderr, "Array index out of bounds: %d (elements: %d)\n", position, strvec->elements);
		return EXIT_FAILURE;
	}

	strvec->vector[position] = string;
	return EXIT_SUCCESS;
}

/*
 * Adds a copy of the string to the vector
 */
int strvec_add(StringVector strvec, char *string) {

	if (string == NULL) {
		fprintf(stderr, "Trying to add NULL string to StringVector\n");
		return EXIT_FAILURE;
	}

	if (strvec == NULL) {
		fprintf(stderr, "NULL StringVector trying to add new string\n");
		return EXIT_FAILURE;
	}

	// checks if the vector has enough space
	// if not, tries to grow the vector
	if (strvec->elements >= strvec->size) {
		if (strvec_grow(strvec) == 0) {
			fprintf(stderr, "Unable to grow the string vector\n");
			return EXIT_FAILURE;
		}
	}

	// creates a copy of the input string
	char *string_copy = (char*) malloc(strlen(string) + 1);
	if (string_copy == NULL) {
		fprintf(stderr, "Error allocating new string for string vector: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	strcpy(string_copy, string);

	// sets the swapped contents
	if (strvec_set(strvec, strvec->elements, string_copy) != EXIT_SUCCESS) {
		fprintf(stderr, "Error adding element at position %d\n", strvec->elements);
		return EXIT_FAILURE;
	}

	strvec->elements++;
	return EXIT_SUCCESS;
}

int strvec_swap(StringVector strvec, unsigned position1, unsigned position2) {

	if (strvec == NULL) {
		fprintf(stderr, "NULL StringVector in strvec_swap\n");
		return EXIT_FAILURE;
	}

	char *element1 = strvec_get(strvec, position1);
	if (element1 == NULL) {
		fprintf(stderr, "Error getting element at position1 %d at strvec_swap()\n", position1);
		return EXIT_FAILURE;
	}

	char *element2 = strvec_get(strvec, position2);
	if (element2 == NULL) {
		fprintf(stderr, "Error getting element at position2 %d at strvec_swap()\n", position2);
		return EXIT_FAILURE;
	}

	if (strvec_set(strvec, position1, element2) != EXIT_SUCCESS) {
		fprintf(stderr, "Error setting element at position1 %d\n", position1);
		return EXIT_FAILURE;
	}

	if (strvec_set(strvec, position2, element1) != EXIT_SUCCESS) {
		fprintf(stderr, "Error setting element at position1 %d\n", position1);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void strvec_free(StringVector strvec) {

	if (strvec == NULL) {
		fprintf(stderr, "NULL StringVector passed in freeStringVector\n");
		return;
	}

	// frees the strings
	for (unsigned i = 0; i < strvec->elements; i++) {
		free(strvec->vector[i]);
	}

	// frees the vector
	free(strvec->vector);
	strvec->vector = NULL;

	// frees the instance
	free(strvec);
}

void strvec_print_status(StringVector strvec) {

	printf("address           : %p\n", strvec);

	if (strvec == NULL) {
		printf("NULL string vector passed at print_status()\n");
		return;
	}

	printf("elements          : %u\n", strvec->elements);
	printf("current size      : %u\n", strvec->size);
	printf("maximum size      : %u\n", strvec->size_max);
	printf("size multiplier   : %u\n", strvec->size_multiplier);
	printf("maximum increments: %u\n", strvec->size_increments_max);
}
