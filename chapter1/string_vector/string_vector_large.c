/*
 * string_vector_large.c
 *
 *  Created on: 14 de mar de 2017
 *      Author: alexandre.mafra
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "string_vector_large.h"

int string_vector_large_allocate_first_block(StringVectorLarge string_vector_large) {

	if (string_vector_large == NULL) {
		fprintf(stderr, "NULL vector passed to string_vector_large_allocate_first_block\n");
		return EXIT_FAILURE;
	}

	string_vector_large->blocks = (StringVector*) calloc(sizeof(StringVector), __NUM_BLOCKS_START_);

	if (string_vector_large->blocks == NULL) {
		fprintf(stderr, "Error allocating large string vector blocks: %s\n", strerror(errno));
		string_vector_large_free(string_vector_large);
		return EXIT_FAILURE;
	}

	string_vector_large->allocated_blocks = __NUM_BLOCKS_START_;

	// allocates the first block (StringVector)
	string_vector_large->blocks[0] = string_vector_create();

	printf("Soon after create first block:\n");
	string_vector_large_print_status(string_vector_large);

	if (string_vector_large->blocks[0] == NULL) {
		fprintf(stderr, "Error allocating first block: %s\n", strerror(errno));
		string_vector_large_free(string_vector_large);
		return EXIT_FAILURE;
	}

	printf("Soon after create first block 2:\n");
	string_vector_large_print_status(string_vector_large);

	//string_vector_large->allocated_blocks = __NUM_BLOCKS_START_;
	string_vector_large->num_blocks = 1;
	string_vector_large->size = string_vector_large->blocks[0]->size;

	printf("Inside create first block:\n");
	string_vector_large_print_status(string_vector_large);
	return EXIT_SUCCESS;
}

StringVectorLarge string_vector_large_create() {

	StringVectorLarge string_vector_large = (StringVectorLarge) malloc(sizeof(StringVectorLarge));

	if (string_vector_large == NULL) {
		fprintf(stderr, "Error allocating large string vector: %s\n", strerror(errno));
		return NULL;
	}

	string_vector_large->num_elements = 0;

	// allocates the array of blocks
	if (__NUM_BLOCKS_START_ == 0) {

		string_vector_large->blocks = NULL;
		string_vector_large->allocated_blocks = 0;
		string_vector_large->num_blocks = 0;
		string_vector_large->size = 0;

	} else {

		if (string_vector_large_allocate_first_block(string_vector_large) != EXIT_SUCCESS) {
			return NULL;
		}
	}

	printf("After create:\n");
	string_vector_large_print_status(string_vector_large);
	return string_vector_large;
}

int string_vector_large_check_position(StringVectorLarge string_vector_large, unsigned long position) {

	printf("Checking position %ld\n", position);
	fflush(stdout);

	if (string_vector_large == NULL) {
		fprintf(stderr, "NULL string_vector_large at string_vector_large_check_position\n");
		return EXIT_FAILURE;
	}

	if (position >= string_vector_large->num_elements - 1) {
		fprintf(stderr, "Element index out of range in string_vector_large_check_position: %ld (elements: %ld)\n", position,
				string_vector_large->num_elements);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

StringVector string_vector_large_get_block(StringVectorLarge string_vector_large, unsigned long position) {

	if (string_vector_large_check_position(string_vector_large, position) != EXIT_SUCCESS) {
		fprintf(stderr, "Error getting position's block\n");
		return NULL;
	}

	unsigned block_index = position / __MEM_BLOCK_SIZE_MAX_;
	printf("string_vector_large->blocks: %p\n", string_vector_large->blocks);
	printf("string_vector_large->blocks[%d]: %p\n", block_index, string_vector_large->blocks[block_index]);
	return string_vector_large->blocks[block_index];
}

StringVector string_vector_large_get_current_block(StringVectorLarge string_vector_large) {
	return string_vector_large_get_block(string_vector_large, string_vector_large->num_elements);
}

int string_vector_large_allocate_block(StringVectorLarge string_vector_large) {

	if (string_vector_large == NULL) {
		fprintf(stderr, "NULL string_vector_large in string_vector_large_allocate_block\n");
		return EXIT_FAILURE;
	}

	// checks if the block index must grow
	if (string_vector_large->num_blocks >= string_vector_large->allocated_blocks) {

		unsigned allocated_blocks_cur = string_vector_large->num_blocks;
		unsigned allocated_blocks_new = allocated_blocks_cur + __NUM_BLOCKS_INCREMENT_;
		string_vector_large->blocks = (StringVector*) realloc(string_vector_large->blocks,
				allocated_blocks_new * sizeof(StringVector));

		if (string_vector_large->blocks == NULL) {
			fprintf(stderr, "Error allocating block index (new size: %d): %s\n", allocated_blocks_new, strerror(errno));
			return EXIT_FAILURE;
		}

		string_vector_large->allocated_blocks += __NUM_BLOCKS_INCREMENT_;
	}

	StringVector string_vector_new = string_vector_create();

	if (string_vector_new == NULL) {
		fprintf(stderr, "Error creating new block\n");
		return EXIT_FAILURE;
	}

	string_vector_large->blocks[string_vector_large->num_blocks] = string_vector_new;
	string_vector_large->num_blocks++;

	return EXIT_SUCCESS;
}

int string_vector_large_grow(StringVectorLarge string_vector_large) {

	if (string_vector_large == NULL) {
		fprintf(stderr, "NULL large string vector passed to string_vector_grow()\n");
		return EXIT_FAILURE;
	}

	// gets the current block
	StringVector string_vector_cur = string_vector_large_get_current_block(string_vector_large);

	if (string_vector_cur == NULL) {

		// first block must be allocated
		if (string_vector_large_allocate_first_block(string_vector_large) != EXIT_SUCCESS) {
			fprintf(stderr, "Error trying to grow large string vector\n");
			return EXIT_FAILURE;
		}

		string_vector_cur = string_vector_large->blocks[0];
	}

	// tries to grow the current block
	if (string_vector_can_grow(string_vector_cur)) {

		unsigned growth = string_vector_grow(string_vector_cur);
		if (growth == 0) {
			fprintf(stderr, "Error growing current StringVector block\n");
			return EXIT_FAILURE;
		}

		string_vector_large->size += growth;
		return EXIT_SUCCESS;
	}

	// can't grow current block: allocate a new block
	if (string_vector_large_allocate_block(string_vector_large) != EXIT_SUCCESS) {
		fprintf(stderr, "Error allocating new block for large string vector\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

char *string_vector_large_get(StringVectorLarge string_vector_large, unsigned long position) {

	StringVector string_vector_pos = string_vector_large_get_block(string_vector_large, position);

	if (string_vector_pos == NULL) {
		fprintf(stderr, "Error getting position's block at string_vector_large_get()\n");
		return NULL;
	}

	// gets the string at the position in the block
	unsigned element_index = position % __MEM_BLOCK_SIZE_MAX_ - 1;
	return string_vector_get(string_vector_pos, element_index);
}

int string_vector_large_set(StringVectorLarge string_vector_large, unsigned long position, char *string) {

	StringVector string_vector_pos = string_vector_large_get_block(string_vector_large, position);

	if (string_vector_pos == NULL) {
		fprintf(stderr, "Error getting position's block at string_vector_large_set()\n");
		return EXIT_FAILURE;
	}

	// gets the string at the position in the block
	unsigned element_index = position % __MEM_BLOCK_SIZE_MAX_ - 1;
	return string_vector_set(string_vector_pos, element_index, string);
}

int string_vector_large_add(StringVectorLarge string_vector_large, char *string) {

	if (string_vector_large == NULL) {
		fprintf(stderr, "NULL StringVectorLarge trying to add new string\n");
		return EXIT_FAILURE;
	}

	printf("elements: %ld; size: %ld\n", string_vector_large->num_elements, string_vector_large->size);
	fflush(stdout);

	// checks if vector is full
	if (string_vector_large->num_elements >= string_vector_large->size) {
		printf("trying to grow large string vector\n");
		if (string_vector_large_grow(string_vector_large) != EXIT_SUCCESS) {
			fprintf(stderr, "Error growing large string vector");
			return EXIT_FAILURE;
		}
		printf("large string vector grow to %ld bytes\n", string_vector_large->size);
		fflush(stdout);
	}

	// adds the string to the current block
	StringVector string_vector_cur = string_vector_large_get_current_block(string_vector_large);

	if (string_vector_cur == NULL) {
		fprintf(stderr, "Error getting current block in large string vector\n");
		return EXIT_FAILURE;
	}

	if (string_vector_add(string_vector_cur, string) != EXIT_SUCCESS) {
		fprintf(stderr, "Error adding new string to the current block in large string vector\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int string_vector_large_swap(StringVectorLarge string_vector_large, unsigned long position1, unsigned long position2) {

	char *string1 = string_vector_large_get(string_vector_large, position1);
	char *string2 = string_vector_large_get(string_vector_large, position2);

	if (string_vector_large_set(string_vector_large, position1, string2) != EXIT_SUCCESS) {
		fprintf(stderr, "Error setting at position 1 (%ld)\n", position1);
		return EXIT_FAILURE;
	}

	if (string_vector_large_set(string_vector_large, position2, string1) != EXIT_SUCCESS) {
		fprintf(stderr, "Error setting at position 2 (%ld)\n", position2);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void string_vector_large_free(StringVectorLarge string_vector_large) {

	if (string_vector_large == NULL) {
		return;
	}

	for (int block = 0; block < string_vector_large->num_blocks; block++) {
		string_vector_free(string_vector_large->blocks[block]);
		string_vector_large->blocks[block] = NULL;
	}

	string_vector_large->num_elements = 0;
	string_vector_large->size = 0;
	free(string_vector_large->blocks);

	string_vector_large->blocks = NULL;
	string_vector_large->num_blocks = 0;
	string_vector_large->allocated_blocks = 0;
}

void string_vector_large_print_status(StringVectorLarge string_vector_large) {

	if (string_vector_large == NULL) {
		printf("NULL large string vector\n");
		return;
	}

	printf("string_vector_large: %p\n", string_vector_large);
	printf("blocks pointer     : %p\n", string_vector_large->blocks);
	printf("first block pointer: %p\n", string_vector_large->blocks[0]);
	printf("allocated blocks   : %d\n", string_vector_large->allocated_blocks);
	printf("used blocks        : %d\n", string_vector_large->num_blocks);
	printf("allocated size     : %ld\n", string_vector_large->size);
	printf("used size          : %ld\n", string_vector_large->num_elements);
}
