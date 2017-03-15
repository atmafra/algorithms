/*
 * string_vector_large.c
 *
 *  Created on: 14 de mar de 2017
 *      Author: alexandre.mafra
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "string_vector_large.h"

/*
 * Creates a new StringVectorLarge
 */
StringVectorLarge string_vector_large_create() {

	StringVectorLarge string_vector_large = (StringVectorLarge) malloc(
			sizeof(StringVectorLarge));

	if (string_vector_large == NULL) {
		fprintf(stderr, "Error allocating large string vector: %s\n",
				strerror(errno));
		return NULL;
	}

	string_vector_large->num_elements = 0;
	string_vector_large->size = __MEM_BLOCK_SIZE_START_ * __NUM_BLOCKS_START_;
	string_vector_large->blocks = (StringVector*) calloc(sizeof(StringVector*),
			__NUM_BLOCKS_START_);

	if (string_vector_large->blocks == NULL) {
		fprintf(stderr, "Error allocating large string vector blocks: %s\n", strerror(errno));
		return NULL;
	}

	return string_vector_large;
}

/*
 * Grows the vector according to the specified parameters
 */
int string_vector_grow(StringVectorLarge string_vector_large) {

	if (string_vector_large == NULL) {
		fprintf(stderr, "NULL large string vector passed to string_vector_grow()\n");
		return EXIT_FAILURE;
	}

	unsigned cur_size = string_vector_large->size;
	unsigned new_size = cur_size + ;

	if (new_size > __MEM_BLOCK_SIZE_MAX_) {
		fprintf(stderr,
				"Cannot grow string_vector to size %d (maximum is %d)\n",
				new_size, __MEM_BLOCK_SIZE_MAX_);
		return EXIT_FAILURE;
	}

	string_vector->vector = (char**) realloc(string_vector->vector,
			new_size * sizeof(char*));
	if (string_vector->vector == NULL) {
		fprintf(stderr, "Error allocating %d bytes to the vector: %s\n",
				new_size, strerror(errno));
		return EXIT_FAILURE;
	}

	string_vector->size = new_size;
	return EXIT_SUCCESS;
}
/*
 * Adds a new string to the vector
 */
int string_vector_large_add(StringVectorLarge string_vector_large,
		char *string) {

	if (string == NULL) {
		fprintf(stderr, "Trying to add NULL string to StringVectorLarge\n");
		return EXIT_FAILURE;
	}

	if (string_vector_large == NULL) {
		fprintf(stderr, "NULL StringVectorLarge trying to add new string\n");
		return EXIT_FAILURE;
	}

	if (string_vector_large->num_elements >= string_vector_large->size) {

		// try to allocate new blocks
		string_vector_large->blocks = (StringVector*) realloc(string_vector_large, )
	}

	return EXIT_SUCCESS;
}
