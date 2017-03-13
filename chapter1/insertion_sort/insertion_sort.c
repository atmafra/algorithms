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

#ifndef __MAX_LINES_
#define __MAX_LINES_ 100000
#endif

#ifndef __LINE_SIZE_
#define __LINE_SIZE_ 1000
#endif

char **list;

StringVector read_input_file(char *file_name) {

	if (file_name == 0) {
		fprintf(stderr, "Empty file name\n");
		return NULL;
	}

	FILE *fp = fopen(file_name, "r");

	if (fp == NULL) {
		fprintf(stderr, "Error reading file\n");
		return NULL;
	}

	StringVector string_vector = string_vector_create(__MAX_LINES_);

	char buffer[__LINE_SIZE_];
	int vector_add_status = EXIT_SUCCESS;

	while ((fgets(buffer, __LINE_SIZE_, fp) != NULL) && (vector_add_status == EXIT_SUCCESS)) {
		vector_add_status = string_vector_add(string_vector, buffer);
	}

	printf("Read %d lines\n", string_vector->numElements);
	fclose(fp);

	return string_vector;
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

	StringVector string_vector = read_input_file(argv[1]);
	int num_elements = string_vector->numElements;

	/* insertion sort */
	printf("Sorting %d elements\n", num_elements);
	fflush(stdout);
	int i, j;

	for (i = 1; i < num_elements; i++) {

		j = i;

		while ((j > 0)
				&& (strcmp(string_vector_get(string_vector, j),
						string_vector_get(string_vector, j - 1)) < 0)) {
			string_vector_swap(string_vector, j, j - 1);
			j -= 1;
		}

		if (i%1000 == 0) {
			printf("Currently at %d\n", i);
		}
	}

	for (i = 0; i < num_elements; i++) {
		printf("%s\n", string_vector_get(string_vector, i));
	}

	string_vector_free(string_vector);

	return EXIT_SUCCESS;
}
