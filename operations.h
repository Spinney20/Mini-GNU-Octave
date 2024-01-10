// Copyright Dobre Andrei-Teodor 314CA 2023-2024

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "allocations.h"

int verify_index(int index, int index_array);
int verify_multiplication(int_matrix *mat_arr, int indx1, int indx2, int size);
int_matrix read_matrix(int rows, int cols);
void print_matrix(int_matrix *mat_arr, int index_array);
void load_matrix(int_matrix **mat_arr, int *size, int *capacity);
void transfer_matrix(int_matrix *source, int_matrix *destination);
void dimmensions(int_matrix *mat_arr, int index_array);
void resize(int_matrix *mat_arr, int size);
void transposition(int_matrix *mat_arr, int size);
void multiply(int_matrix *mat_arr, int index1, int index2, int size);
void multiplication(int_matrix **mat_arr, int *size, int *capacity);
int sum_of_elements(int_matrix *matrix);
void swap(int_matrix *a, int_matrix *b);
void sort(int_matrix *mat_arr, int size);
void multiplication_for_power(int_matrix A, int_matrix B);
void raise_to_pow(int_matrix *mat_arr, int size);
void strassen(int_matrix a, int_matrix b, int_matrix c);
void break_matrix(int_matrix parent, int_matrix A11,
				  int_matrix A12, int_matrix A21, int_matrix A22);
void join_matrices(int_matrix c11, int_matrix c12, int_matrix c21,
				   int_matrix c22, int_matrix *result);
void add(int_matrix a, int_matrix b, int_matrix c);
void subtract(int_matrix a, int_matrix b, int_matrix c);
void allocate_strassen(int_matrix *arr, int new_rows);
void calculate_m1_to_m7(int_matrix *arr);
void calculate_c11_to_c22(int_matrix *arr);
void implement_strassen(int_matrix **mat_arr, int *size, int *capacity);
void elimination(int_matrix **mat_arr, int *size, int *capacity);
