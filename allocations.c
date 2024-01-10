// Copyright Dobre Andrei-Teodor 314CA 2023-2024

#include <stdio.h>
#include <stdlib.h>
#include "allocations.h"

// Function for allocating. memory for an array
int *allocate_arr(int n)
{
	int *vector = (int *)malloc(n * sizeof(int));

	// Defensive programming
	if (!vector) {
		printf("malloc() failed\n");
		exit(-1);
	}

	return vector;
}

// Function for reading an array
void read_array(int *vector, int n)
{
	for (int i = 0; i < n; i++)
		scanf("%d", &vector[i]);
}

// Function for allocating memory for a matrix
int_matrix allocate_matrix(int rows, int cols)
{
	// Doing this so it won't be necessary to update the rows and cols
	// everytime I initialize a new matrix
	int_matrix matrix;
	matrix.rows = rows;
	matrix.cols = cols;

	// Memory allocation for a matrix
	matrix.values = (int **)malloc(rows * sizeof(int *));
	for (int i = 0; i < rows; i++)
		matrix.values[i] = (int *)malloc(cols * sizeof(int));

	// Defensive programming
	if (!matrix.values) {
		printf("malloc() failed\n");
		exit(-1);
	}

	return matrix;
}

// Function for freeing memory of a matrix
void free_matrix(int rows, int_matrix matrix)
{
	for (int i = 0; i < rows; i++)
		free(matrix.values[i]);
	free(matrix.values);
}

// Function for firstly verifying if the resizable array is full
// and if it's full doubling its capacity
void double_capacity(int_matrix **mat_arr, int *size, int *capacity)
{
	//Verifying if the array is full
	if (*size == *capacity) {
		// If the array is full we double its capacity and realloc memory
		*capacity *= 2;
		*mat_arr = realloc(*mat_arr, (*capacity) * sizeof(int_matrix));
	}

	// Defensive programming
	if (!mat_arr) {
		printf("realloc() failed\n");
		exit(-1);
	}
}

// Function for firstly verifying if the resizable array is half empty
// and if its half empty halving its capacity
void halve_capacity(int_matrix **mat_arr, int *size, int *capacity)
{
	// Verifying if the array is half empty
	if (*size < (*capacity / 2)) {
		// If the array is half empty we reduce its capacity by half
		*capacity /= 2;
		*mat_arr = realloc(*mat_arr, (*capacity) * sizeof(int_matrix));
	}

	// Defensive programming
	if (!mat_arr) {
		printf("realloc() failed\n");
		exit(-1);
	}
}

// This function frees an array of matrices
// It is used for the Q command and the Strassen Algorithm
void free_matrix_array(int_matrix *mat_arr, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < mat_arr[i].rows; j++)
			free(mat_arr[i].values[j]);
		free(mat_arr[i].values);
	}
	free(mat_arr);
}
