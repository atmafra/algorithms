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
#include <stdbool.h>
#include "string_vector.h"

/*
 * Allocates a new StringVector
 */
StringVector string_vector_create() {

	StringVector string_vector = (StringVector) malloc(sizeof(StringVector));

	if (string_vector == NULL) {
		fprintf(stderr, "Error allocating string vector: %s\n", strerror(errno));
		return NULL;
	}

	string_vector->num_elements = 0;
	string_vector->size = __MEM_BLOCK_SIZE_START_;
	string_vector->vector = (char**) calloc(sizeof(char*),
	__MEM_BLOCK_SIZE_START_);

	if (string_vector->vector == NULL) {
		fprintf(stderr, "Error allocating string vector internal array: %s\n", strerror(errno));
		return NULL;
	}

	return string_vector;
}

/*
 * Returns the new size if the string vector can grow
 */
unsigned string_vector_new_size(StringVector string_vector) {

	if (string_vector == NULL) {
		fprintf(stderr, "NULL string vector passed to sting_vector_can_grow()\n");
		return 0;
	}

	unsigned cur_size = string_vector->size;
	unsigned new_size = cur_size * __MEM_BLOCK_SIZE_MULTIPLIER_;

	if (new_size > __MEM_BLOCK_SIZE_MAX_) {
		return cur_size;
	} else {
		return new_size;
	}
}

/*
 * Returns true if the vector can grow by 1 element
 */
bool string_vector_can_grow(StringVector string_vector) {

	if (string_vector == NULL) {
		fprintf(stderr, "NULL string vector passed for string_vector_can_grow\n");
		return false;
	}

	if (string_vector_new_size(string_vector) > string_vector->size) {
		return true;
	} else {
		return false;
	}
}

/*
 * Grows the vector according to the specified parameters
 * Returns the allocation growth
 */
unsigned string_vector_grow(StringVector string_vector) {

	if (string_vector == NULL) {
		fprintf(stderr, "NULL string vector passed to string_vector_grow()\n");
		return 0;
	}

	unsigned cur_size = string_vector->size;
	unsigned new_size = string_vector_new_size(string_vector);

	if (new_size <= cur_size) {
		fprintf(stderr, "Cannot grow string_vector (maximum size is %d)\n",
		__MEM_BLOCK_SIZE_MAX_);
		return 0;
	}

	string_vector->vector = (char**) realloc(string_vector->vector, new_size * sizeof(char*));

	if (string_vector->vector == NULL) {
		fprintf(stderr, "Error allocating %d bytes to the vector: %s\n", new_size, strerror(errno));
		return 0;
	}

	string_vector->size = new_size;
	return new_size - cur_size;
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
		fprintf(stderr, "Position out of bounds: %d (%d elements)\n", position, string_vector->num_elements);
		return NULL;
	}

	return string_vector->vector[position];
}

/*
 * Sets the string at position
 */
int string_vector_set(StringVector string_vector, unsigned position, char *string) {

	if (string_vector == NULL) {
		fprintf(stderr, "NULL vector passed to string_vector_set()\n");
		return EXIT_FAILURE;
	}

	if (position > string_vector->num_elements) {
		fprintf(stderr, "Array index out of bounds: %d (elements: %d)\n", position, string_vector->num_elements);
		return EXIT_FAILURE;
	}

	string_vector->vector[position] = string;
	return EXIT_SUCCESS;
}

/*
 * Adds a copy of the string to the vector
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

	// checks if the vector has enough space
	// if not, tries to grow the vector
	if (string_vector->num_elements >= string_vector->size) {
		if (string_vector_grow(string_vector) == 0) {
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
	if (string_vector_set(string_vector, string_vector->num_elements, string_copy) != EXIT_SUCCESS) {
		fprintf(stderr, "Error adding element at position %d\n", string_vector->num_elements);
		return EXIT_FAILURE;
	}

	string_vector->num_elements++;
	return EXIT_SUCCESS;
}

/**
 * Swaps the elements in two positions
 */
int string_vector_swap(StringVector string_vector, unsigned position1, unsigned position2) {

	if (string_vector == NULL) {
		fprintf(stderr, "NULL StringVector in string_vector_swap\n");
		return EXIT_FAILURE;
	}

	char *element1 = string_vector_get(string_vector, position1);
	if (element1 == NULL) {
		fprintf(stderr, "Error getting element at position1 %d at string_vector_swap()\n", position1);
		return EXIT_FAILURE;
	}

	char *element2 = string_vector_get(string_vector, position2);
	if (element2 == NULL) {
		fprintf(stderr, "Error getting element at position2 %d at string_vector_swap()\n", position2);
		return EXIT_FAILURE;
	}

	if (string_vector_set(string_vector, position1, element2) != EXIT_SUCCESS) {
		fprintf(stderr, "Error setting element at position1 %d\n", position1);
		return EXIT_FAILURE;
	}

	if (string_vector_set(string_vector, position2, element1) != EXIT_SUCCESS) {
		fprintf(stderr, "Error setting element at position1 %d\n", position1);
		return EXIT_FAILURE;
	}

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

	// frees the strings
	for (unsigned i = 0; i < string_vector->num_elements; i++) {
		free(string_vector->vector[i]);
	}

	// frees the vector
	free(string_vector->vector);
	string_vector->vector = NULL;

	// frees the instance
	free(string_vector);
}

void string_vector_print_status(StringVector string_vector) {

	printf("address : %p\n", string_vector);

	if (string_vector == NULL) {
		printf("NULL string vector passed at print_status()\n");
		return;
	}
	printf("size    : %d\n", string_vector->size);
	printf("elements: %d\n", string_vector->num_elements);
}
