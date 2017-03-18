/*
 * strvlg.h
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

	unsigned long elements;
	unsigned long size;
	unsigned blocks;
	unsigned blocks_allocated;
	StringVector *vector;

} StringVectorLargeType;

typedef StringVectorLargeType *StringVectorLarge;

/*
 * Allocates a new StringVectorLarge
 */
StringVectorLarge strvlg_create();

/*
 * Adds a new string to the vector
 */
/**
 * Gets the string at position
 */
char *strvlg_get(StringVectorLarge strvlg, unsigned long position);

/*
 * Sets the string at position
 */
int strvlg_set(StringVectorLarge strvlg, unsigned long position, char *string);

/**
 * Swaps the elements in two positions
 */
int strvlg_add(StringVectorLarge strvlg, char *new_string);

/*
 * Swaps the strings between two positions
 */
int strvlg_swap(StringVectorLarge strvlg, unsigned long position1, unsigned long position2);

/**
 * Frees all memory allocated
 */
void strvlg_free(StringVectorLarge strvlg);

/*
 * Prints the status
 */
void strvlg_print_status(StringVectorLarge strvlg);

/*
 * Prints the vector
 */
void strvlg_print(StringVectorLarge strvlg);

#endif /* strvlg_H_ */
