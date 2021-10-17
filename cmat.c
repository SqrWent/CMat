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
    for (int i = 0; i < row; i++) {
        A->mat[i] = (double _Complex *) malloc(col * sizeof(double _Complex));
    }
}


//Free a matrix, don't use it on uninitialized matrix.
void FreMat(mat *A) {
    for (int i = 0; i < A->row; i++) {
        free(A->mat[i]);
        A->mat[i] = NULL;
    }
    free(A->mat);
    A->mat = NULL;
}


//Get the transpose of a matrix and save the result to result, allowing the use of TraMat(&A, &A)
void TraMat(mat *A, mat *result) {
    if ((A->row != result->col) | (A->col != result->row))
        perror("The dimension of output matrix doesn't match that of input one.");

    //Following steps allow the use of TraMat(&A, &A)
    if (A->row == A->col) {
        double _Complex temp;
        for (int i = 0; i < A->row; i++) {
            for (int j = 0; j < i + 1; j++) {
                if (i == j) {
                    result->mat[i][i] = A->mat[i][i];
                } else {
                    temp = A->mat[i][j];
                    result->mat[i][j] = A->mat[j][i];
                    result->mat[j][i] = temp;
                }
            }
        }
    } else {
        for (int i = 0; i < A->row; i++) {
            for (int j = 0; j < A->col; j++) {
                result->mat[j][i] = A->mat[i][j];
            }
        }
    }
}


//Get the conjugation of a matrix, allowing the use of CojMat(&A, &A)
void CojMat(mat *A, mat *result) {
    if ((A->row != result->row) | (A->col != result->col))
        perror("The dimension of output matrix doesn't match that of input one.");
    for (int i = 0; i < A->row; i++) {
        for (int j = 0; j < A->col; j++) {
            result->mat[i][j] = conj(A->mat[i][j]);
        }
    }
}


//Set all elements of a matrix to be zero
void ZeroMat(mat *A) {
    for (int i = 0; i < A->row; i++) {
        for (int j = 0; j < A->col; j++) {
            A->mat[i][j] = 0;
        }
    }
}


//ZeroInitialize the matrix
void ZIniMat(mat *A, int row, int col) {
    IniMat(A, row, col);
    ZeroMat(A);
}


//Initial a matrix as identity of dimension dim
void IIniMat(mat *A, int dim) {
    IniMat(A, dim, dim);
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            A->mat[i][j] = (i == j) ? 1 : 0;
        }
    }
}
