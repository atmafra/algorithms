/*
 * strvlg.h
 *
 *  Created on: 14 de mar de 2017
 *      Author: alexandre.mafra
 */

#ifndef STRING_VECTOR_LARGE_H_
#define STRING_VECTOR_LARGE_H_

#include "string_vector.h"

typedef struct {

	unsigned long elements;
	unsigned long size;
	unsigned long size_max;
	unsigned size_initial;
	unsigned size_multiplier;
	unsigned size_increments_max;
	unsigned blocks;
	unsigned blocks_increment;
	unsigned blocks_max_increments;
	unsigned blocks_allocated;
	unsigned blocks_max;
	unsigned blocks_size_max;
	StringVector *vector;

} StringVectorLargeType;

typedef StringVectorLargeType *StringVectorLarge;

/**
 * Default sizes
 */
extern const unsigned strvlg_blocks_initial_default;
extern const unsigned strvlg_blocks_increments_max_default;
extern const unsigned strvlg_blocks_max;
extern const unsigned strvlg_blocks_increment_default;

/**
 * Allocates the first block (string vector)
 * @param strvlg large string vector
 * @param initial_size initial string vector size
 * @param initial_blocks initial number of allocated blocks
 * @return EXIT_SUCCESS/EXIT_FAILURE
 */
int strvlg_allocate_first_block(StringVectorLarge strvlg, unsigned long initial_size, unsigned initial_blocks);

/**
 * Allocates a new StringVectorLarge with parameters
 * @param initial_size block initial size
 * @param size_multiplier block size multiplier
 * @param max_size_increments maximum increments per block
 * @param initial_blocks initial number of blocks
 * @param blocks_increment number of additional blocks created on growth
 * @param blocks_increments_max maximum number of block increments
 * @return new large string vector; NULL in case of error
 */
StringVectorLarge strvlg_create(unsigned long initial_size, unsigned size_multiplier, unsigned max_size_increments,
		unsigned initial_blocks, unsigned blocks_increment, unsigned blocks_increments_max);

/**
 * Allocates a new StringVectorLarge with default parameter values
 * @return new large string vector; NULL in case of error
 */
StringVectorLarge strvlg_create_default();

/**
 * Grows a large string vector
 * @param strvlg large string vector
 * @param initial_blocks initial number of blocks
 * @return
 */
int strvlg_grow(StringVectorLarge strvlg, unsigned initial_blocks);

/**
 * Gets the string at the position
 * @param strvlg large string vector
 * @param position position in the vector
 * @return string at the position; NULL in case of error
 */
char *strvlg_get(StringVectorLarge strvlg, unsigned long position);

/**
 * Sets the string at the position
 * @param strvlg large string vector
 * @param position position to be set
 * @param string new string value
 * @return EXIT_SUCCESS/EXIT_FAILURE
 */
int strvlg_set(StringVectorLarge strvlg, unsigned long position, char *string);

/**
 * Adds a new string in the end of the vector
 * @param strvlg large string vector
 * @param string string to be added
 * @return EXIT_SUCCESS/EXIT_FAILURE
 */
int strvlg_add(StringVectorLarge strvlg, char *string, unsigned initial_blocks);

/**
 * Swaps the strings between two positions
 * @param strvlg large string vector
 * @param position1 first position
 * @param position2 second position
 * @return EXIT_SUCCESS/EXIT_FAILURE
 */
int strvlg_swap(StringVectorLarge strvlg, unsigned long position1, unsigned long position2);

/**
 * Frees all memory allocated
 * @param strvlg large string vector
 */
void strvlg_free(StringVectorLarge strvlg);

/**
 * Outputs the status of the large string vector to the standard output
 * @param strvlg large string vector
 */
void strvlg_print_status(StringVectorLarge strvlg);

/**
 * Outputs all the strings in order to the standard output
 * @param strvlg large string vector
 */
void strvlg_print(StringVectorLarge strvlg);

#endif /* STRING_VECTOR_LARGE_H_ */
