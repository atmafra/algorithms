/*
 * strvlg.c
 *
 *  Created on: 14 de mar de 2017
 *      Author: alexandre.mafra
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "string_vector_large.h"

int strvlg_allocate_first_block(StringVectorLarge strvlg) {

	if (strvlg == NULL) {
		fprintf(stderr, "NULL vector passed to strvlg_allocate_first_block\n");
		return EXIT_FAILURE;
	}

	strvlg->vector = (StringVector*) calloc(sizeof(StringVector), __NUM_BLOCKS_START_);

	if (strvlg->vector == NULL) {
		fprintf(stderr, "Error allocating large string vector blocks: %s\n", strerror(errno));
		strvlg_free(strvlg);
		return EXIT_FAILURE;
	}

	strvlg->blocks_allocated = __NUM_BLOCKS_START_;

	// allocates the first block (StringVector)
	strvlg->vector[0] = strvec_create_default();

	if (strvlg->vector[0] == NULL) {
		fprintf(stderr, "Error allocating first block: %s\n", strerror(errno));
		strvlg_free(strvlg);
		return EXIT_FAILURE;
	}

	strvlg->size = strvlg->vector[0]->size;
	strvlg->blocks = 1;
	return EXIT_SUCCESS;
}

StringVectorLarge strvlg_create() {

	StringVectorLarge strvlg = (StringVectorLarge) malloc(sizeof(StringVectorLargeType));

	if (strvlg == NULL) {
		fprintf(stderr, "Error allocating large string vector: %s\n", strerror(errno));
		return NULL;
	}

	strvlg->blocks_allocated = 0;
	strvlg->blocks = 0;
	strvlg->size = 0;
	strvlg->elements = 0;
	strvlg->vector = NULL;

	// allocates the array of blocks
	if (__NUM_BLOCKS_START_ > 0) {
		if (strvlg_allocate_first_block(strvlg) != EXIT_SUCCESS) {
			return NULL;
		}
	}

	return strvlg;
}

int strvlg_check_position(StringVectorLarge strvlg, unsigned long position) {

	if (strvlg == NULL) {
		fprintf(stderr, "NULL strvlg at strvlg_check_position\n");
		return EXIT_FAILURE;
	}

	if (position >= strvlg->elements - 1) {
		fprintf(stderr, "Element index out of range in strvlg_check_position: %ld (elements: %ld)\n", position,
				strvlg->elements);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

StringVector strvlg_get_block(StringVectorLarge strvlg, unsigned long position) {

	unsigned block_index = (unsigned) position / strvec_size_max;
	return strvlg->vector[block_index];
}

StringVector strvlg_get_current_block(StringVectorLarge strvlg) {

	if (strvlg->size == 0) {
		return NULL;
	}

	if (strvlg->elements == 0) {
		return strvlg_get_block(strvlg, 0);
	}

	unsigned long current_position = strvlg->elements - 1;
	return strvlg_get_block(strvlg, current_position);
}

int strvlg_allocate_block(StringVectorLarge strvlg) {

	if (strvlg == NULL) {
		fprintf(stderr, "NULL strvlg in strvlg_allocate_block\n");
		return EXIT_FAILURE;
	}

	// checks if the block index must grow
	if (strvlg->blocks >= strvlg->blocks_allocated) {

		unsigned allocated_blocks_cur = strvlg->blocks;
		unsigned allocated_blocks_new = allocated_blocks_cur + __NUM_BLOCKS_INCREMENT_;

		strvlg->vector = (StringVector*) realloc(strvlg->vector,
				allocated_blocks_new * sizeof(StringVector));

		if (strvlg->vector == NULL) {
			fprintf(stderr, "Error allocating block index (new size: %d): %s\n", allocated_blocks_new, strerror(errno));
			return EXIT_FAILURE;
		}

		strvlg->blocks_allocated += __NUM_BLOCKS_INCREMENT_;
	}

	StringVector string_vector_new = strvec_create_default();

	if (string_vector_new == NULL) {
		fprintf(stderr, "Error creating new block\n");
		return EXIT_FAILURE;
	}

	strvlg->vector[strvlg->blocks] = string_vector_new;
	strvlg->size += string_vector_new->size;
	strvlg->blocks++;

	return EXIT_SUCCESS;
}

int strvlg_grow(StringVectorLarge strvlg) {

	if (strvlg == NULL) {
		fprintf(stderr, "NULL large string vector passed to string_vector_grow()\n");
		return EXIT_FAILURE;
	}

	// gets the current block
	StringVector string_vector_cur = strvlg_get_current_block(strvlg);

	if (string_vector_cur == NULL) {

		// first block must be allocated
		if (strvlg_allocate_first_block(strvlg) != EXIT_SUCCESS) {
			fprintf(stderr, "Error trying to grow large string vector\n");
			return EXIT_FAILURE;
		}

		string_vector_cur = strvlg->vector[0];
	}

	// tries to grow the current block
	if (strvec_can_grow(string_vector_cur) == true) {

		unsigned growth = strvec_grow(string_vector_cur);
		if (growth == 0) {
			fprintf(stderr, "Error growing current StringVector block\n");
			return EXIT_FAILURE;
		}

		strvlg->size += growth;
		return EXIT_SUCCESS;
	}

	// can't grow current block: allocate a new block
	if (strvlg_allocate_block(strvlg) != EXIT_SUCCESS) {
		fprintf(stderr, "Error allocating new block for large string vector\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

char *strvlg_get(StringVectorLarge strvlg, unsigned long position) {

	StringVector string_vector_pos = strvlg_get_block(strvlg, position);

	if (string_vector_pos == NULL) {
		fprintf(stderr, "Error getting position's block at strvlg_get()\n");
		return NULL;
	}

	// gets the string at the position in the block
	unsigned element_index = position % __STRVEC_SIZE_MAX_;
	return strvec_get(string_vector_pos, element_index);
}

int strvlg_set(StringVectorLarge strvlg, unsigned long position, char *string) {

	StringVector string_vector_pos = strvlg_get_block(strvlg, position);

	if (string_vector_pos == NULL) {
		fprintf(stderr, "Error getting position's block at strvlg_set()\n");
		return EXIT_FAILURE;
	}

	// gets the string at the position in the block
	unsigned element_index = position % __STRVEC_SIZE_MAX_;
	return strvec_set(string_vector_pos, element_index, string);
}

int strvlg_add(StringVectorLarge strvlg, char *string) {

	if (strvlg == NULL) {
		fprintf(stderr, "NULL StringVectorLarge trying to add new string\n");
		return EXIT_FAILURE;
	}

	// checks if vector is full
	if (strvlg->elements >= strvlg->size) {
		if (strvlg_grow(strvlg) != EXIT_SUCCESS) {
			fprintf(stderr, "Error growing large string vector");
			return EXIT_FAILURE;
		}
	}

	// adds the string to the current block
	StringVector string_vector_cur = strvlg_get_block(strvlg, strvlg->elements);

	if (string_vector_cur == NULL) {
		fprintf(stderr, "Error getting current block in large string vector\n");
		return EXIT_FAILURE;
	}

	if (strvec_add(string_vector_cur, string) != EXIT_SUCCESS) {
		fprintf(stderr, "Error adding new string to the current block in large string vector\n");
		return EXIT_FAILURE;
	}

	strvlg->elements++;
	return EXIT_SUCCESS;
}

int strvlg_swap(StringVectorLarge strvlg, unsigned long position1, unsigned long position2) {

	char *string1 = strvlg_get(strvlg, position1);
	char *string2 = strvlg_get(strvlg, position2);

	if (strvlg_set(strvlg, position1, string2) != EXIT_SUCCESS) {
		fprintf(stderr, "Error setting at position 1 (%ld)\n", position1);
		return EXIT_FAILURE;
	}

	if (strvlg_set(strvlg, position2, string1) != EXIT_SUCCESS) {
		fprintf(stderr, "Error setting at position 2 (%ld)\n", position2);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void strvlg_free(StringVectorLarge strvlg) {

	if (strvlg == NULL) {
		return;
	}

	for (unsigned block = 0; block < strvlg->blocks; block++) {
		strvec_free(strvlg->vector[block]);
		strvlg->vector[block] = NULL;
	}

	strvlg->elements = 0;
	strvlg->size = 0;
	free(strvlg->vector);

	strvlg->vector = NULL;
	strvlg->blocks = 0;
	strvlg->blocks_allocated = 0;
}

void strvlg_print_status(StringVectorLarge strvlg) {

	if (strvlg == NULL) {
		printf("NULL large string vector\n");
		return;
	}

	printf("elements        : %lu\n", strvlg->elements);
	printf("allocated size  : %lu\n", strvlg->size);
	printf("blocks used     : %d\n", strvlg->blocks);
	printf("blocks allocated: %d\n", strvlg->blocks_allocated);
	printf("address         : %p\n", strvlg);
	printf("blocks address  : %p\n", strvlg->vector);
	printf("first block     : %p\n", strvlg->vector[0]);
	printf("current block   : %p\n", strvlg_get_current_block(strvlg));
}

void strvlg_print(StringVectorLarge strvlg) {

	if (strvlg == NULL) {
		printf("NULL large string vector at print()\n");
		return;
	}

	for (unsigned long i = 0; i < strvlg->elements; i++) {
		char *string = strvlg_get(strvlg, i);
		printf("%s\n", string);
	}
}
