/*
 * insertion_sort.c
 *
 *  Created on: 12 de mar de 2017
 *      Author: mafra
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "string_vector_large.h"

#ifndef __MAX_LINES_
#define __MAX_LINES_ 100000
#endif

#ifndef __LINE_SIZE_
#define __LINE_SIZE_ 1000
#endif

int read_input_file(char *file_name, StringVectorLarge strvlg, unsigned initial_blocks) {

	if (file_name == 0) {
		fprintf(stderr, "Empty file name\n");
		return EXIT_FAILURE;
	}

	FILE *fp = fopen(file_name, "r");

	if (fp == NULL) {
		fprintf(stderr, "Error opening file '%s' for reading: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	char buffer[__LINE_SIZE_ ];
	int vector_add_status = EXIT_SUCCESS;

	while ((fgets(buffer, __LINE_SIZE_, fp) != NULL) && (vector_add_status == EXIT_SUCCESS)) {

		strtok(buffer, "\n");

		if (strvlg_add(strvlg, buffer, initial_blocks) != EXIT_SUCCESS) {
			fprintf(stderr, "Error adding element '%s' to string vector\n", buffer);
			fclose(fp);
			return EXIT_FAILURE;
		}
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {

	char *filename;

	if (argc > 1) {
		filename = argv[1];
		printf("Reading file '%s'\n", filename);
	} else {
		fprintf(stderr, "No input file name\n");
		return EXIT_FAILURE;
	}

	StringVectorLarge strvlg = strvlg_create(strvec_size_initial_default, strvec_size_multiplier_default,
			strvec_size_increments_max_default, strvlg_blocks_initial_default, strvlg_blocks_increment_default,
			strvlg_blocks_increments_max_default);

	if (strvlg == NULL) {
		fprintf(stderr, "Error creating large string vector\n");
		exit(EXIT_FAILURE);
	}

	if (read_input_file(filename, strvlg, strvlg_blocks_initial_default) != EXIT_SUCCESS) {
		fprintf(stderr, "Error reading input file\n");
		strvlg_free(strvlg);
		exit(EXIT_FAILURE);
	}

	unsigned long num_elements = strvlg->elements;

	/* insertion sort */
	//printf("\nSorting %lu elements\n", num_elements);
	unsigned long i, j;

	for (i = 1; i < num_elements; i++) {

		j = i;

		while ((j > 0) && (strcmp(strvlg_get(strvlg, j), strvlg_get(strvlg, j - 1)) < 0)) {
			strvlg_swap(strvlg, j, j - 1);
			j -= 1;
		}

		if (i % 1000 == 0) {
			printf("Currently at %lu\n", i);
		}
	}

	strvlg_print(strvlg);
	strvlg_free(strvlg);
	return EXIT_SUCCESS;
}
