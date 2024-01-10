// Copyright Dobre Andrei-Teodor 314CA 2023-2024

#include <stdio.h>
#include <stdlib.h>

#include "allocations.h"

#define MOD 10007

// Function for verifying that there is a matrix at the given index
int verify_index(int index, int index_array)
{
	if (index_array <= index || index < 0)
		return 0;
	else
		return 1;
}

// Function for verifying if the multiplication operation can take place
int verify_multiplication(int_matrix *mat_arr, int indx1, int indx2, int size)
{
	if (verify_index(indx1, size) == 0 || verify_index(indx2, size) == 0) {
		printf("No matrix with the given index\n");
		return 0;
	} else if (mat_arr[indx1].cols != mat_arr[indx2].rows) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	return 1;
}

// Function for reading a matrix from STDIN and also allocating memory for it
int_matrix read_matrix(int rows, int cols)
{
	// Before reading it is necessary to allocate memory;
	int_matrix matrix = allocate_matrix(rows, cols);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			scanf("%d", &matrix.values[i][j]);

	return matrix;
}

// Function for printing a matrix - COMMAND 'P'
void print_matrix(int_matrix *mat_arr, int index_array)
{
	// Reading the index
	int index;
	scanf("%d", &index);
	// Verifying the index;
	if (verify_index(index, index_array) == 0) {
		printf("No matrix with the given index\n");
	} else {
		// Printing the matrix with the given index from the resizable array
		int_matrix matrix = mat_arr[index];
		for (int i = 0; i < matrix.rows; i++) {
			for (int j = 0; j < matrix.cols; j++)
				printf("%d ", matrix.values[i][j]);
			printf("\n");
		}
	}
}

// Function for loading a matrix in the memory, read from STDIN
// Command 'L'
void load_matrix(int_matrix **mat_arr, int *size, int *capacity)
{
	// Reading the rows and cols
	int rows, cols;
	scanf("%d %d", &rows, &cols);

	// Reading the matrix
	int_matrix matrix = read_matrix(rows, cols);

	// If the array is full we double its capacity
	double_capacity(mat_arr, size, capacity);

	// Storing the matrix at the end of the array
	(*mat_arr)[(*size)++] = matrix;
}

// Function for transfering a matrix in another matrix (source to destination)
// used widely in the program in functions such as:
// resize, transpose, raise_pow (where we use temporary matrices);
void transfer_matrix(int_matrix *source, int_matrix *destination)
{
	// both matrices have the same dimensions

	// Copy values from the source to the destination;
	for (int i = 0; i < source->rows; i++)
		for (int j = 0; j < source->cols; j++)
			destination->values[i][j] = source->values[i][j];
}

// Function for determining a matrix's with a given index dimmensions
// COMMAND 'D'
void dimmensions(int_matrix *mat_arr, int index_array)
{
	// Reading the index
	int index;
	scanf("%d", &index);

	// Verifying the index
	if (verify_index(index, index_array) == 0)
		printf("No matrix with the given index\n");
	else
		// Printing the rows and cols of the matrix with the given index;
		printf("%d %d\n", mat_arr[index].rows, mat_arr[index].cols);
}

// Function for resizing a matrix according to given instructions
// COMMAND 'C'
void resize(int_matrix *mat_arr, int size)
{
	int index;
	scanf("%d", &index);

	int redim_rows;
	scanf("%d", &redim_rows);

	// I keep rows indexes in an array
	int *rows_arr = allocate_arr(redim_rows);
	read_array(rows_arr, redim_rows);

	int redim_cols;
	scanf("%d", &redim_cols);

	// I keep colums indexes in an array
	int *cols_arr = allocate_arr(redim_cols);
	read_array(cols_arr, redim_cols);

	// Verifying the existance of the matrix
	if (verify_index(index, size) == 0) {
		printf("No matrix with the given index\n");
		free(rows_arr);
		free(cols_arr);
	} else {
		// I allocate a temporary matrix
		int_matrix tmp_matrix = allocate_matrix(redim_rows, redim_cols);

		// I store the values wanted in the tmp_matrix
		for (int i = 0; i < redim_rows; i++)
			for (int j = 0; j < redim_cols; j++)
				// rows and cols from the array
				tmp_matrix.values[i][j] =
				mat_arr[index].values[rows_arr[i]][cols_arr[j]];

		// Freeing the initial matrix
		free_matrix(mat_arr[index].rows, mat_arr[index]);

		// Allocating a new matrix at the given index
		// With the new rows and cols ofc
		mat_arr[index] = allocate_matrix(redim_rows, redim_cols);

		// Storing the desired matrix in the place of the old matrix
		// aka transfering the tmp_matrix back to the place of the initial mat
		transfer_matrix(&tmp_matrix, &mat_arr[index]);

		// Freeing the memory
		free_matrix(tmp_matrix.rows, tmp_matrix);
		free(rows_arr);
		free(cols_arr);
	}
}

// Function for the transposition of a matrix
// COMMAND 'T'
void transposition(int_matrix *mat_arr, int size)
{
	int index;
	scanf("%d", &index);

	//Verifying if there is a matrix at the given index
	if (verify_index(index, size) == 0) {
		printf("No matrix with the given index\n");
	} else {
		// We allocate the tmp matrix with the rows and cols exchanged
		int_matrix tmp_matrix =
		allocate_matrix(mat_arr[index].cols, mat_arr[index].rows);

		// We store the transposed matrix in the tmp, because we want to
		// get rid of it from the array of matrices
		for (int i = 0; i < mat_arr[index].cols; i++)
			for (int j = 0; j < mat_arr[index].rows; j++)
				//rows and cols exchanged
				tmp_matrix.values[i][j] = mat_arr[index].values[j][i];

		// Freeing the initial matrix
		free_matrix(mat_arr[index].rows, mat_arr[index]);

		// Allocating the tranposed matrix (with rows and cols exchanged)
		// in the place of the old matrix
		mat_arr[index] =
		allocate_matrix(mat_arr[index].cols, mat_arr[index].rows);

		// Storing the tranposed matrix in the initial index
		transfer_matrix(&tmp_matrix, &mat_arr[index]);

		// Freeing the temporary matrix
		free_matrix(tmp_matrix.rows, tmp_matrix);
	}
}

// Performing the multiplications of 2 matrices, and storing the result
// in the resizable array
// USED FOR MULTIPLICATION function
void multiply(int_matrix *mat_arr, int index1, int index2, int size)
{
	// Allocating the matrix at the end of the resizable array
	mat_arr[size] =
	allocate_matrix(mat_arr[index1].rows, mat_arr[index2].cols);

	//Performing the multiplication ( % 10007 )
	for (int i = 0; i < mat_arr[index1].rows; i++) {
		for (int j = 0; j < mat_arr[index2].cols; j++) {
			mat_arr[size].values[i][j] = 0;
			for (int k = 0; k < mat_arr[index1].cols; k++) {
				if (mat_arr[index1].values[i][k]
					* mat_arr[index2].values[k][j] >= 0)
					mat_arr[size].values[i][j] +=
					((mat_arr[index1].values[i][k]
						* mat_arr[index2].values[k][j]) % MOD);
				else
					mat_arr[size].values[i][j] +=
					(mat_arr[index1].values[i][k]
					* mat_arr[index2].values[k][j]) % MOD + MOD;
			}
		}
	}

	for (int i = 0; i < mat_arr[size].rows; i++)
		for (int j = 0; j < mat_arr[size].cols; j++)
			mat_arr[size].values[i][j] = mat_arr[size].values[i][j] % MOD;
}

// This function implements the multiplication done in the function 'multiply'
// when the Command 'M' is introduced in STDIN
// Command 'M'
void multiplication(int_matrix **mat_arr, int *size, int *capacity)
{
	int index1, index2;
	scanf("%d%d", &index1, &index2);

	//Verifying if the multiplication is possible
	if (verify_multiplication(*mat_arr, index1, index2, *size)) {
		//If the array is full we double its capacity
		double_capacity(mat_arr, size, capacity);

		//Performing the multiplication
		multiply(*mat_arr, index1, index2, *size);

		//Incrementing the size because we added a matrix
		(*size)++;
	}
}

// Function for determing the sum of all elements of a matrix;
// This function will be needed in the sort function
int sum_of_elements(int_matrix *matrix)
{
	int sum = 0;
	for (int i = 0; i < matrix->rows; i++) {
		for (int j = 0; j < matrix->cols; j++) {
			sum += matrix->values[i][j];
			sum %= MOD;
			if (sum < 0)
				sum += MOD;
		}
	}
	return sum;
}

// Function for swaping to values
void swap(int_matrix *a, int_matrix *b)
{
	int_matrix temp = *a;
	*a = *b;
	*b = temp;
}

// Function for sorting the matrices in the array of matrices
// This functions sorts the matrices by the sum of their elements
// Command 'O'
void sort(int_matrix *mat_arr, int size)
{
	int exchanged = 1;

	while (exchanged) {
		exchanged = 0;

		for (int i = 0; i < size - 1; i++) {
			int a, b;
			a = sum_of_elements(&mat_arr[i]);
			b = sum_of_elements(&mat_arr[i + 1]);

			if (a > b) {
				// swaping the values
				swap(&mat_arr[i], &mat_arr[i + 1]);

				// marking the exchangement done
				exchanged = 1;
			}
		}
	}
}

// Multiplying operation specially designed for the raise_pow function
void multiplication_for_power(int_matrix A, int_matrix B)
{
	int rows = A.rows;

	// Allocating a temporary matrix in which we will store the product
	// before putting it in the matrix A
	int_matrix C = allocate_matrix(rows, rows);

	// In order to perform the power operation the given matrices will be
	// square matrices
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			C.values[i][j] = 0;
			for (int k = 0; k < rows; k++) {
				if (A.values[i][k] * B.values[k][j] >= 0)
					C.values[i][j] += ((A.values[i][k] * B.values[k][j]) % MOD);
				else
					C.values[i][j] +=
					(A.values[i][k] * B.values[k][j]) % MOD + MOD;
			}
		}
	}

	// Taking in consideration that the given matrices are square matrices
	// Copying the result in the first matrix is simple
	// because the result will have the same rows and cols like its 'parents'
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			C.values[i][j] = C.values[i][j] % MOD;
			A.values[i][j] = C.values[i][j];
		}
	}

	//Freeing the temporary matrix
	free_matrix(rows, C);
}

void raise_to_pow(int_matrix *mat_arr, int size)
{
	int index, power;
	scanf("%d %d", &index, &power);
	if (verify_index(index, size) == 0) {
		printf("No matrix with the given index\n");
		return;
	}
	if (power < 0) {
		printf("Power should be positive\n");
		return;
	}
	int rows = mat_arr[index].rows;
	int cols = mat_arr[index].cols;
	if (rows != cols) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	//Allocation of a temporary matrix needed for storing intermediate results
	int_matrix tmp = allocate_matrix(rows, rows);

	// For the beggining copying the initial matrix in the tmp matrix
	transfer_matrix(&mat_arr[index], &tmp);

	// Decrementing the power by one
	power--;

	// The algorithm
	while (power > 0) {
		if (power % 2 == 1)
			multiplication_for_power(mat_arr[index], tmp);

		multiplication_for_power(tmp, tmp);
		power /= 2;
	}

	//Freeing the temporary matrix
	free_matrix(rows, tmp);
}

// FROM HERE, THE STRASSEN ALGORITHM BEGINS
void strassen(int_matrix a, int_matrix b, int_matrix c);

void break_matrix(int_matrix parent, int_matrix A11,
				  int_matrix A12, int_matrix A21, int_matrix A22)
{
	// Strassen algorithm works only for matrices with dimensions that are
	// power of 2, and its rows are equal to its cols
	// So we divde the parents rows by 2 (also rows = cols);
	int new_rows = parent.rows / 2;

	for (int i = 0; i < A11.rows; i++) {
		for (int j = 0; j < A11.rows; j++) {
			A11.values[i][j] = parent.values[i][j];
			A12.values[i][j] = parent.values[i][j + new_rows];
			A21.values[i][j] = parent.values[i + new_rows][j];
			A22.values[i][j] = parent.values[i + new_rows][j + new_rows];
		}
	}
}

// Function for joining the C matrices and forming the result in Strassen
void join_matrices(int_matrix c11, int_matrix c12, int_matrix c21,
				   int_matrix c22, int_matrix *result)
{
	int new_rows = c11.rows;

	// Joining 4 matrices for the Strassen algorithm as it follows:
	// C11 UP-LEFT
	// C12 UP-RIGHT
	// C21 DOWN-LEFT
	// C22 DOWN-RIGHT
	for (int i = 0; i < new_rows; i++) {
		for (int j = 0; j < new_rows; j++) {
			result->values[i][j] = c11.values[i][j];
			result->values[i][j + new_rows] = c12.values[i][j];
			result->values[i + new_rows][j] = c21.values[i][j];
			result->values[i + new_rows][j + new_rows] = c22.values[i][j];
		}
	}
}

void add(int_matrix a, int_matrix b, int_matrix c)
{
	int rows = a.rows;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < rows; j++) {
			c.values[i][j] = (a.values[i][j] + b.values[i][j]) % MOD;
			if (c.values[i][j] < 0)
				c.values[i][j] += MOD;
		}
}

void subtract(int_matrix a, int_matrix b, int_matrix c)
{
	int rows = a.rows;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < rows; j++) {
			c.values[i][j] = (a.values[i][j] - b.values[i][j]) % MOD;
			if (c.values[i][j] < 0)
				c.values[i][j] += MOD;
		}
}

// Function for allocating all the matrices needed for strassen algorithm
void allocate_strassen(int_matrix *arr, int new_rows)
{
	// We are allocating the matrices in an array of matrices
	// in order to keep the code clear
	for (int i = 0; i < 21; i++)
		arr[i] = allocate_matrix(new_rows, new_rows);

	// Each matrix that we allocated is explained below:
	//For more clarity about what A11, A12 etc. means -> see Strassen Algorithm

	// A11 = arr[0]
	// A12 = arr[1]
	// A21 = arr[2]
	// A22 = arr[3]
	// B11 = arr[4]
	// B12 = arr[5]
	// B21 = arr[6]
	// B22 = arr[7]

	// M1 = arr[8]
	// M2 = arr[9]
	// M3 = arr[10]
	// M4 = arr[11]
	// M5 = arr[12]
	// M6 = arr[13]
	// M7 = arr[14]

	// These matrices are used to hold temporary values
	// aresult = arr[15]
	// bresult = arr[16]

	// C11 = arr[17]
	// C12 = arr[18]
	// C21 = arr[19]
	// C22 = arr[20]
}

void calculate_m1_to_m7(int_matrix *arr)
{
	// Calculating M1 to M7:

	// a11 + a22
		add(arr[0], arr[3], arr[15]);
	// b11 + b22
		add(arr[4], arr[7], arr[16]);
	// M1 = (a11 + a22) * (b11 + b22)
		strassen(arr[15], arr[16], arr[8]);

	// a21 + a22
		add(arr[2], arr[3], arr[15]);
	// M2 = (a21 + a22) * b11
		strassen(arr[15], arr[4], arr[9]);

	// b12 - b22
		subtract(arr[5], arr[7], arr[16]);
	// M3 = a11 * (b12 - b22)
		strassen(arr[0], arr[16], arr[10]);

	// b21 - b11
		subtract(arr[6], arr[4], arr[16]);
	// M4 = a22 * (b21 - b11)
		strassen(arr[3], arr[16], arr[11]);

	// a11 + a12
		add(arr[0], arr[1], arr[15]);
	// M5 = (a11+a12) * b22
		strassen(arr[15], arr[7], arr[12]);

	// a21 - a11
		subtract(arr[2], arr[0], arr[15]);
	// b11 + b12
		add(arr[4], arr[5], arr[16]);
	// M6 = (a21 - a11) * (b11 + b12)
		strassen(arr[15], arr[16], arr[13]);

	// a12 - a22
		subtract(arr[1], arr[3], arr[15]);
	// b21 + b22
		add(arr[6], arr[7], arr[16]);
	// M7 = (a12 - a22) * (b21 + b22)
		strassen(arr[15], arr[16], arr[14]);
}

void calculate_c11_to_c22(int_matrix *arr)
{
	// Calculating C11, C12, C21, C22:

	// C11 = m1 + m4 - m5 + m7
	// a = m1 + m4
	add(arr[8], arr[11], arr[15]);
	// b = a - m5 = m1 + m4 - m5
	subtract(arr[15], arr[12], arr[16]);
	// c11 = b + m7 = m1 + m4 - m5 + m7
	add(arr[16], arr[14], arr[17]);

	// C12 = m3 + m5
	add(arr[10], arr[12], arr[18]);

	// C21 = m2 + m4
	add(arr[9], arr[11], arr[19]);

	// C22 = m1 + m3 - m2 + m6
	//  a =  m1 + m3
	add(arr[8], arr[10], arr[15]);
	// b = a - m2 = m1 + m3 - m2
	subtract(arr[15], arr[9], arr[16]);
	// c22 = m1 + m3 - m2 + m6
	add(arr[16], arr[13], arr[20]);
}

void strassen(int_matrix a, int_matrix b, int_matrix c)
{
	// Doing Strassen until the broken matrices have 1 row & 1 col
	if (a.rows == 1) {
		c.values[0][0] = a.values[0][0] * b.values[0][0];
	} else {
		int new_rows = a.rows / 2;

		// We keep all the matrices needed to complete the strassen algorithm
		// in an array of matrices for the clarity of the code
		// All the matrices are explained in the allocate_strassen function
		int_matrix *arr = (int_matrix *)malloc(21 * sizeof(int_matrix));
		allocate_strassen(arr, new_rows);

		// We break each matrix in 4 submatrices
		// Breaking the first matrix
		break_matrix(a, arr[0], arr[1], arr[2], arr[3]);
		// Breaking the second matrix;
		break_matrix(b, arr[4], arr[5], arr[6], arr[7]);

		// Calculating M1, M2, M3, M4, M5, M6, M7
		calculate_m1_to_m7(arr);

		// Calculatin C11, C12, C21, C22
		calculate_c11_to_c22(arr);

		// Joining C11, C12, C21, C22 in the result matrix
		join_matrices(arr[17], arr[18], arr[19], arr[20], &c);

		// Freeing the memory
		free_matrix_array(arr, 21);
	}
}

// This function implements Strassen Algorithm when the command 'S' is called
void implement_strassen(int_matrix **mat_arr, int *size, int *capacity)
{
	// Scanning the indexes after the S command
	int indx1, indx2;
	scanf("%d %d", &indx1, &indx2);

	// Verifying if the multiplication is possible
	if (verify_multiplication(*mat_arr, indx1, indx2, *size)) {
		// If the array is full we double its capacity
		double_capacity(mat_arr, size, capacity);

		// Incrementing the size because we add one more matrix to the array
		(*size)++;

		// Allocating the memory for the result at the end of the array
		// Knowing that Strassen works only for square matrices we
		// will allocate with parents rows
		(*mat_arr)[*size - 1] =
		allocate_matrix((*mat_arr)[indx1].rows, (*mat_arr)[indx1].rows);

		// Performing the Strassen multiplication and adding the result
		// at the end of the array where we specially allocated memory for it
		strassen((*mat_arr)[indx1], (*mat_arr)[indx2], (*mat_arr)[*size - 1]);
	}
}

// Function for eliminating a matrix of a given index
// Command - 'F'
void elimination(int_matrix **mat_arr, int *size, int *capacity)
{
	int index;
	scanf("%d", &index);
	if (verify_index(index, *size) == 0) {
		printf("No matrix with the given index\n");
	} else {
		// Freeing the matrix with the given index
		free_matrix((*mat_arr)[index].rows, (*mat_arr)[index]);

		// From the given index
		// Moving all the matrices one place to the left
		for (int i = index; i < (*size) - 1; i++)
			(*mat_arr)[i] = (*mat_arr)[i + 1];

		// Decrementing the size because we removed one matrix
		(*size)--;

		// If the array is half empty, we reduce its capacity
		halve_capacity(mat_arr, size, capacity);
	}
}
