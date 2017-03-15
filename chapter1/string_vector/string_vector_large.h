/*
 * string_vector_large.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: alexandre.mafra
 */

#ifndef STRING_VECTOR_LARGE_H_
#define STRING_VECTOR_LARGE_H_

#include "string_vector.h"

#ifndef __NUM_BLOCKS_START_
#define __NUM_BLOCKS_START_ 10
#endif

#ifndef __NUM_BLOCKS_INCREMENT_
#define __NUM_BLOCKS_INCREMENT_ 10
#endif

#ifndef __NUM_BLOCKS_MAX_
#define __NUM_BLOCKS_MAX_ 1000000
#endif

typedef struct {
	unsigned long num_elements;
	unsigned long size;
	unsigned num_blocks;
	unsigned allocated_blocks;
	StringVector *blocks;
} string_vector_large_struct;

typedef string_vector_large_struct *StringVectorLarge;

/*
 * Creates a new StringVectorLarge
 */
StringVectorLarge string_vector_large_create();

/*
 * Adds a new string to the vector
 */
int string_vector_large_add(StringVectorLarge string_vector_large,
		char *new_string);

/**
 * Gets the string at position
 */
char *string_vector_large_get(StringVectorLarge string_vector_large,
		unsigned position);

/**
 * Swaps the elements in two positions
 */
int string_vector_large_swap(StringVectorLarge string_vector_large,
		unsigned position1, unsigned position2);

/**
 * Frees all memory allocated to the StringVector
 */
void string_vector_large_free(StringVectorLarge string_vector_large);

#endif /* STRING_VECTOR_LARGE_H_ */
