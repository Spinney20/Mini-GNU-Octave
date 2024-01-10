// Copyright Dobre Andrei-Teodor 314CA 2023-2024

#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int **values;
	int rows;
	int cols;
} int_matrix;

int *allocate_arr(int n);
void read_array(int *vector, int n);
int_matrix allocate_matrix(int rows, int cols);
void free_matrix(int rows, int_matrix matrix);
void double_capacity(int_matrix **mat_arr, int *size, int *capacity);
void halve_capacity(int_matrix **mat_arr, int *size, int *capacity);
void free_matrix_array(int_matrix *mat_arr, int size);
