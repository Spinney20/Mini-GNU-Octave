#### Copyright Dobre Andrei-Teodor 314CA 2023-2024

# OCTAVE SIMULATOR

## Overview
I use a matrix structure to store the matrices, the number of their rows, and
the number of their columns. To store matrices in memory simultaneously, I use
an array of structures. All arrays are allocated dynamically.

The project is divided into the following files:
- allocations.h and allocations.c :
these files handle memory allocation and deallocation for matrices and the
int_matrix structure is also defined in allocations.h.
- operations.h and operations.c:
these files contains the operations done to the matrices
- myoctave.c: this file includes the main function which manages the
interaction with matrices using the functions from allocations.c and
operations.c.

The program is structured around the main function which manages input data and
matrix proccessing. Initially, I initialize the resizable array structure to
store matrices. The variable size tracks the arrays size and capacity tracks
its capacity helping the process of resizing the array when needed.

## Implementation

Afterward I create an infinite loop which works as follows:

- Exiting the loop occurs **when the 'Q' command** is read from the keyboard.
First, all memory is released, then quit is updated to 1 and the program exits
the while.

**Command 'L' - Loading a new matrix into memory**
I call the load_matrix function, where:

- I read the matrix from the keyboard using the read_matrix function
incorporating the allocate_matrix function to allocate the necessary
memory for the read matrix.
- After reading the matrix, we check if the array is full (size == capacity).
- If the array is full, I double its size with realloc, then store the matrix
at the end of the array.
- If the array is not full, I only store the matrix at the end of the array.

**Command 'D' - Determining the dimensions of a matrix**

Since I used structures, determining the dimensions is trivial using the
dimmensions function:
- I verify that the index read from the keyboard corresponds to a matrix,
then I display the rows and columns of that matrix.

**Command 'P' - Displaying a matrix**

I call the print_matrix function, where:

- I check the read index, and if it corresponds to a matrix, I display that
matrix.

**Command 'C' - Resizing a matrix**

I call the resize function, where:

- I store row and column indices in two different vectors.
- I check if the matrix exists in the resizable array. If it doesn't, I display
an error message and release the allocated memory for the index vectors.
- I resize the matrix using the two vectors and transfer the desired values to
a dynamically allocated temporary matrix.
- I free the initial matrix because I no longer need it.
- I allocate memory accordingly in place of the old matrix.
- I copy the data from the temporary matrix to the initial matrix's location.
- I free the memory of the temporary matrix and the two vectors.

**Command 'M' - Multiplication of two matrices**

I call the multiplication function, where:

- I read the two indices and check if there are matrices at those indices.
- I check the possibility of multiplying the two matrices.
- I check if the matrix array is "full" in which case I double its capacity
and dynamically reallocate the array.
- I multiply the two matrices % 10007.
- I store the result matrix at the end of the array.

**Command 'T' - Transposition of a matrix**

I call the transposition function, where:

- I check the existence of the matrix at the given index.
- If the matrix exists, I transpose the given matrix into a temporary matrix
whose memory is allocated accordingly (rows swapped with columns).
- I free the old matrix.
- I allocate memory for the transposed matrix in place of the initial matrix.
- I copy the temporary matrix into the initial matrix's location.
- I free the memory of the temporary matrix.

**Command 'O' - Sorting matrices based on the sum of elements**

I call the sort function, working as follows:

- I adapted the bubble sort algorithm to sort matrices based on the sum of
elements, calculated using the sum_of_elements function. The while loop
runs until exchanged remains 0 (no more changes occurd).

**Command 'R' - Matrix exponentiation in logarithmic time**

I call the raise_pow function, where:

- I check the existence of the matrix at the given index and that the exponent
is positive.
- I implemented the algorithm for logarithmic time matrix exponentiation:
Using the multiply_for_power function, designed specifically for the
raise_to_pow function, I multiply matrices according to the logarithmic time
exponentiation algorithm, storing the multiplication result in the first
argument of the function.

**Command 'S' - Matrix multiplication with Strassen's algorithm**

I call the implement_strassen function, where:

- I check if the multiplication with Strassen's algorithm is possible.
- I check if the matrix array is full.
- I allocate memory specifically for the multiplication result at the end of
the array.
- I call the Strassen algorithm and store the result where ive just allocated
memory.
