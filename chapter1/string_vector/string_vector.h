/*
 * string_vector.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: mafra
 */
#include <stdbool.h>

#ifndef STRING_VECTOR_H_
#define STRING_VECTOR_H_

#ifndef __MEM_BLOCK_SIZE_START_
#define __MEM_BLOCK_SIZE_START_ 16
#endif

#ifndef __MEM_BLOCK_SIZE_MULTIPLIER_
#define __MEM_BLOCK_SIZE_MULTIPLIER_ 2
#endif

#ifndef __MEM_BLOCK_SIZE_MAX_
#define __MEM_BLOCK_SIZE_MAX_ 65536
#endif

typedef struct {

	unsigned num_elements;
	unsigned size;
	char **vector;

} StringVectorType;

typedef StringVectorType *StringVector;

/**
 * Creates a new StringVector
 */
StringVector string_vector_create();

/*
 * Returns true if the vector can grow by 1 element
 */
bool string_vector_can_grow(StringVector string_vector);

/*
 * Grows the vector according to the specified parameters
 */
unsigned string_vector_grow(StringVector string_vector);

/**
 * Gets the string at position
 */
char *string_vector_get(StringVector string_vector, unsigned position);

/*
 * Sets the string at position with a copy of the string
 */
int string_vector_set(StringVector string_vector, unsigned position, char *string);

/*
 * Adds a copy of the string to the vector
 */
int string_vector_add(StringVector string_vector, char *string);

/**
 * Swaps the elements in two positions
 */
int string_vector_swap(StringVector string_vector, unsigned position1, unsigned position2);

/**
 * Frees all memory allocated to the StringVector
 */
void string_vector_free(StringVector string_vector);

/*
 * Prints the vector status
 */
void string_vector_print_status(StringVector string_vector);

#endif /* STRING_VECTOR_H_ */
