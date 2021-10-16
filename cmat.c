#include "cmat.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <omp.h>

//This file defines basic matrix operations like creating matrix and free matrix etc.


//Initialize a matrix with row and column numbers given
void IniMat(mat *A, int row, int col) {
    A->row = row;
    A->col = col;
    A->mat = (double _Complex **) malloc(row * sizeof(double _Complex *));
#pragma omp parallel for
    for (int i = 0; i < row; i++) {
        A->mat[i] = (double _Complex *) malloc(col * sizeof(double _Complex));
    }
}


//Free a matrix, don't use it on uninitialized matrix.
void FreMat(mat *A) {
#pragma omp parallel for
    for (int i = 0; i < A->row; i++) {
        free(A->mat[i]);
        A->mat[i] = NULL;
    }
    free(A->mat);
    A->mat = NULL;
}


//Get the transpose of a matrix and save the result to result
void TraMat(mat *A, mat *result) {
#pragma omp parallel for
    for (int i = 0; i < A->row; i++) {
        for (int j = 0; j < A->col; j++) {
            result->mat[j][i] = A->mat[i][j];
        }
    }
}


//Get the conjugate of a matrix
void CojMat(mat *A, mat *result) {
#pragma omp parallel for
    for (int i = 0; i < A->row; i++) {
        for (int j = 0; j < A->col; j++) {
            result->mat[i][j] = conj(A->mat[i][j]);
        }
    }
}


//Set all elements of a matrix to be zero
void ZeroMat(mat A) {
#pragma omp parallel for
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            A.mat[i][j] = 0;
        }
    }
}

