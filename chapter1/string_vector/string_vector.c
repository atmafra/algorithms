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
StringVector string_vector_create() {

	StringVector string_vector = (StringVector) malloc(sizeof(StringVector));

	if (string_vector == NULL) {
		fprintf(stderr, "Error allocating string vector: %s\n",
				strerror(errno));
		return NULL;
	}

	string_vector->num_elements = 0;
	string_vector->size = __MEM_BLOCK_SIZE_START_;
	string_vector->vector = (char**) calloc(sizeof(char*),
			__MEM_BLOCK_SIZE_START_);

	if (string_vector->vector == NULL) {
		fprintf(stderr, "Error allocating string vector internal array: %s\n",
				strerror(errno));
		return NULL;
	}

	return string_vector;
}

/*
 * Grows the vector according to the specified parameters
 */
int string_vector_grow(StringVector string_vector) {

	if (string_vector == NULL) {
		fprintf(stderr, "NULL string vector passed to string_vector_grow()\n");
		return EXIT_FAILURE;
	}

	unsigned cur_size = string_vector->size;
	unsigned new_size = cur_size * __MEM_BLOCK_SIZE_MULTIPLIER_;

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
int string_vector_add(StringVector string_vector, char *string) {

	if (string == NULL) {
		fprintf(stderr, "Trying to add NULL string to StringVector\n");
		return EXIT_FAILURE;
	}

	if (string_vector == NULL) {
		fprintf(stderr, "NULL StringVector trying to add new string\n");
		return EXIT_FAILURE;
	}

	if (string_vector->num_elements >= string_vector->size) {

		// try to grow the string vector
		if (string_vector_grow(string_vector) != EXIT_SUCCESS) {
			fprintf(stderr, "Unable to grow the string vector\n");
			return EXIT_FAILURE;
		}
	}

	char *new_string = (char*) malloc(strlen(string) + 1);

	if (new_string == NULL) {
		fprintf(stderr, "Error allocating new string for string vector: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	strcpy(new_string, string);
	string_vector->vector[string_vector->num_elements] = new_string;
	string_vector->num_elements++;

	return EXIT_SUCCESS;
}

/**
 * Gets the string at position
 */
char *
string_vector_get(StringVector string_vector, unsigned position) {

	if (string_vector == NULL) {
		fprintf(stderr, "NULL StringVector in function string_vector_get\n");
		return NULL;
	}

	if (position > string_vector->num_elements) {
		fprintf(stderr, "Position out of bounds: %d (%d elements)\n", position,
				string_vector->num_elements);
		return NULL;
	}

	return string_vector->vector[position];
}

/**
 * Swaps the elements in two positions
 */
int string_vector_swap(StringVector string_vector, unsigned position1,
		unsigned position2) {

	if (string_vector == NULL) {
		fprintf(stderr, "NULL StringVector in string_vector_swap\n");
		return EXIT_FAILURE;
	}

	if (position1 >= string_vector->num_elements) {
		fprintf(stderr,
				"Invalid position 1 argument in string_vector_swap: %d (%d elements)\n",
				position1, string_vector->num_elements);
		return EXIT_FAILURE;
	}

	if (position2 >= string_vector->num_elements) {
		fprintf(stderr,
				"Invalid position 2 argument in string_vector_swap: %d (%d elements)\n",
				position2, string_vector->num_elements);
		return EXIT_FAILURE;
	}

	char *element1 = string_vector_get(string_vector, position1);
	char *element2 = string_vector_get(string_vector, position2);
	string_vector->vector[position1] = element2;
	string_vector->vector[position2] = element1;

	return EXIT_SUCCESS;
}

/**
 * Frees all memory allocated by the StringVector
 */
void string_vector_free(StringVector string_vector) {

	if (string_vector == NULL) {
		fprintf(stderr, "NULL StringVector passed in freeStringVector\n");
		return;
	}

	for (unsigned i = 0; i < string_vector->num_elements; i++) {
		free(string_vector->vector[i]);
	}

	free(string_vector->vector);
	string_vector->vector = NULL;
	free(string_vector);
}
