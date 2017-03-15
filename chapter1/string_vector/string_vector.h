/*
 * string_vector.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: mafra
 */

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
} string_vector_struct;

typedef string_vector_struct *StringVector;

/**
 * Creates a new StringVector
 */
StringVector string_vector_create();

/**
 * Adds a new string to the vector
 */
int string_vector_add(StringVector strVec, char *newString);

/**
 * Gets the string at position
 */
char *string_vector_get(StringVector strVec, unsigned position);

/**
 * Swaps the elements in two positions
 */
int string_vector_swap(StringVector strVec, unsigned position1, unsigned position2);

/**
 * Frees all memory allocated to the StringVector
 */
void string_vector_free(StringVector strVec);

#endif /* STRING_VECTOR_H_ */
