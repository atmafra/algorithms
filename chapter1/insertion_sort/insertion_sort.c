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
#include "string_vector.h"
#include "string_vector_large.h"

#ifndef __MAX_LINES_
#define __MAX_LINES_ 100000
#endif

#ifndef __LINE_SIZE_
#define __LINE_SIZE_ 1000
#endif

StringVectorLarge read_input_file(char *file_name) {

	if (file_name == 0) {
		fprintf(stderr, "Empty file name\n");
		return NULL;
	}

	FILE *fp = fopen(file_name, "r");

	if (fp == NULL) {
		fprintf(stderr, "Error reading file\n");
		return NULL;
	}

	StringVectorLarge string_vector_large = string_vector_large_create();

	char buffer[__LINE_SIZE_ ];
	int vector_add_status = EXIT_SUCCESS;

	while ((fgets(buffer, __LINE_SIZE_, fp) != NULL)
			&& (vector_add_status == EXIT_SUCCESS)) {

		strtok(buffer, "\n");

		if (string_vector_large_add(string_vector_large, buffer) != EXIT_SUCCESS) {
			fprintf(stderr, "Error adding element '%s' to string vector\n",
					buffer);
			string_vector_large_free(string_vector_large);
			fclose(fp);
			return NULL;
		}
	}

	fclose(fp);
	return string_vector_large;
}

int main(int argc, char *argv[]) {

	char *filename;

	if (argc > 1) {
		filename = argv[1];
		//printf("Reading file '%s'\n", filename);
	} else {
		fprintf(stderr, "No input file name\n");
		return EXIT_FAILURE;
	}

	StringVectorLarge string_vector_large = read_input_file(argv[1]);

	if (!string_vector_large) {
		fprintf(stderr, "Error reading file '%s'\n", filename);
		exit(EXIT_FAILURE);
	}

	unsigned long num_elements = string_vector_large->num_elements;
	//string_vector_large_print(string_vector_large);
	//exit(EXIT_SUCCESS);

	/* insertion sort */
	//printf("\nSorting %lu elements\n", num_elements);
	unsigned long i, j;

	for (i = 1; i < num_elements; i++) {

		j = i;

		while ((j > 0)
				&& (strcmp(string_vector_large_get(string_vector_large, j),
						string_vector_large_get(string_vector_large, j - 1)) < 0)) {
			string_vector_large_swap(string_vector_large, j, j - 1);
			j -= 1;
		}

		if (i % 1000 == 0) {
			printf("Currently at %lu\n", i);
		}
	}

	string_vector_large_print(string_vector_large);
	string_vector_large_free(string_vector_large);
	return EXIT_SUCCESS;
}
