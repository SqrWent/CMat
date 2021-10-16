//
// Created by 吕文韬 on 2021/10/16.
//

#include "_Basic_Calculate_.h"
#include <math.h>
#include <complex.h>
#include <stdio.h>
#include <omp.h>

//Add two matrices.
void add(mat *A, mat *B, mat *result) {
    if ((A->row != B->row) | (A->col != B->col)) {
        perror("Trying to add two matrices of different sizes.");
    }
#pragma omp parallel for
    for (int i = 0; i < A->row; i++) {
        for (int j = 0; j < A->col; j++) {
            result->mat[i][j] = A->mat[i][j] + B->mat[i][j];
        }
    }
}


//get the minimal value from a,b,c,d
int _Min(int a, int b, int c, int d) {
    int min;
    return d < (min = c < (min = a < b ? a : b) ? c : min) ? d : min;
}


//Normal multiplication of two matrices
void NmMulMat(mat *A, mat *B, mat *result) {
    int sum;
#pragma omp parallel private(sum)
    {
#pragma omp parallel for
        for (int i = 0; i < A->row; i++) {
            for (int j = 0; j < B->col; j++) {
                sum = 0;
                for (int k = 0; k < A->col; k++) {
                    sum += A->mat[i][k] * B->mat[k][j];
                }
                result->mat[i][j] = sum;
            }
        }
    }
}