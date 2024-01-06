// Copyright Dobre Andrei-Teodor 314CA 2023-2024

#include <stdio.h>
#include <stdlib.h>

#include "allocations.h"
#include "operations.h"

int main(void)
{
	char command;
	// Defining the resizable array with its size and capacity
	int capacity = 1, size = 0, quit = 0;
	int_matrix *mat_arr = (int_matrix *)malloc(capacity * sizeof(int_matrix));

	while (quit == 0) {
		scanf(" %c", &command);

		switch (command) {
		case 'Q':
			free_matrix_array(mat_arr, size);

			quit = 1; // Exiting the while loop after freeing all the memory

			break;
		case 'L':
			load_matrix(&mat_arr, &size, &capacity);
			break;
		case 'D':
			dimmensions(mat_arr, size);
			break;
		case 'P':
			print_matrix(mat_arr, size);
			break;
		case 'C':
			resize(mat_arr, size);
			break;
		case 'M':
			multiplication(&mat_arr, &size, &capacity);
			break;
		case 'T':
			transposition(mat_arr, size);
			break;
		case 'O':
			sort(mat_arr, size);
			break;
		case 'R':
			raise_to_pow(mat_arr, size);
			break;
		case 'F':
			elimination(&mat_arr, &size, &capacity);
			break;
		case 'S':
			implement_strassen(&mat_arr, &size, &capacity);
			break;
		default:
			printf("Unrecognized command\n");
			break;
		}
	}
	return 0;
}
