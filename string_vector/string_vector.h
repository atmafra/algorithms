/*
 * strvec.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: mafra
 */
#include <stdbool.h>
#include <math.h>

#ifndef STRING_VECTOR_H_
#define STRING_VECTOR_H_

#ifndef __STRVEC_SIZE_INITIAL_DEFAULT_
#define __STRVEC_SIZE_INITIAL_DEFAULT_ 16
#endif

#ifndef __STRVEC_SIZE_MULTIPLIER_DEFAULT_
#define __STRVEC_SIZE_MULTIPLIER_DEFAULT_ 2
#endif

#ifndef __STRVEC_SIZE_INCREMENTS_MAX_DEFAULT_
#define __STRVEC_SIZE_INCREMENTS_MAX_DEFAULT_ 12
#endif

#ifndef __STRVEC_SIZE_MAX_
#define __STRVEC_SIZE_MAX_ 65536
#endif

typedef struct {

	unsigned elements;
	unsigned size;
	unsigned size_multiplier;
	unsigned size_increments_max;
	unsigned size_max;
	char **vector;

} StringVectorType;

typedef StringVectorType *StringVector;

/**
 * Default sizes
 */
extern const unsigned strvec_size_initial_default;
extern const unsigned strvec_size_multiplier_default;
extern const unsigned strvec_size_increments_max_default;
extern const unsigned strvec_size_max;

/**
 * Creates a new StringVector with size parameters
 */
StringVector strvec_create(unsigned initial_size, unsigned size_multiplier, unsigned max_size_increments);

/**
 * Creates a new StringVector
 */
StringVector strvec_create_default();

/**
 * Returns true if the vector can grow by 1 element
 */
bool strvec_can_grow(StringVector strvec);

/**
 * Grows the vector according to the specified parameters
 */
unsigned strvec_grow(StringVector strvec);

/**
 * Gets the string at position
 */
char *strvec_get(StringVector strvec, unsigned position);

/**
 * Sets the string at position with a copy of the string
 */
int strvec_set(StringVector strvec, unsigned position, char *string);

/**
 * Adds a copy of the string to the vector
 */
int strvec_add(StringVector strvec, char *string);

/**
 * Swaps the elements in two positions
 */
int strvec_swap(StringVector strvec, unsigned position1, unsigned position2);

/**
 * Frees all memory allocated to the StringVector
 */
void strvec_free(StringVector strvec);

/**
 * Prints the vector status
 */
void strvec_print_status(StringVector strvec);

#endif /* strvec_H_ */
