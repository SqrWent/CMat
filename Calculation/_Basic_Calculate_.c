#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
//
// Created by 吕文韬 on 2021/10/16.
//

#include "_Basic_Calculate_.h"
#include <math.h>
#include <complex.h>
#include <stdio.h>
#include<omp.h>


//Add two matrices.
void AddMat(mat *A, mat *B, mat *result) {
    if ((A->row != B->row) | (A->col != B->col)) {
        perror("Trying to add two matrices of different sizes!");
    }
    for (int i = 0; i < A->row; i++) {
        for (int j = 0; j < A->col; j++) {
            result->mat[i][j] = A->mat[i][j] + B->mat[i][j];
        }
    }
}


//Minus two matrics, A-B, save to result
void MnsMat(mat *A, mat *B, mat *result) {
    if ((A->row != B->row) | (A->col != B->col)) {
        perror("Trying to add two matrices of different sizes!");
    }
    for (int i = 0; i < A->row; i++) {
        for (int j = 0; j < A->col; j++) {
            result->mat[i][j] = A->mat[i][j] - B->mat[i][j];
        }
    }
}


//get the minimal value from a,b,c,d
int _Min(int a, int b, int c, int d) {
    int min;
    return d < (min = c < (min = a < b ? a : b) ? c : min) ? d : min;
}


//Normal multiplication of two matrices, result matrix equals to neither A nor B!
void NmMulMat(mat *A, mat *B, mat *result) {
    if (A->col != B->row)
        perror("Trying to multiply matrices with wrong dimensions!");
    if ((result->row != A->row) | (result->col != B->col))
        perror("Dimension of output matrix doesn't match the input ones!");

    double _Complex sum;
#pragma omp parallel for private(sum)
    {
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


//Strassen Multiplication of two matrices.
void StrassenMulMat(mat *A, mat *B, mat *result) {
    //Error information
    if ((A->row != A->col) | (B->row != B->col))
        perror("Strassen Multiplication can only be used for n by n matrices!");
    if ((A->row % 2 != 0) & (A->row != 1))
        perror("Strassen Multiplication can only be used for 2^n by 2^n matrices!");
    if (A->col != B->row)
        perror("Trying to multiply matrices with wrong dimensions!");
    if (result->row != A->row)
        perror("Dimension of output matrix doesn't match the input ones!");

    //Computation
    int dim = A->row;
    if (dim == 1) {
        result->mat[0][0] = A->mat[0][0] * B->mat[0][0];
    } else {
        int i, temp2, j, k, inirow, inicol;
        mat s[10];
        mat p[7];
        for (i = 0; i < 10; i++) {
            IniMat(&s[i], dim / 2, dim / 2);
        }
        for (i = 0; i < 7; i++) {
            IniMat(&p[i], dim / 2, dim / 2);
        }
        mat a[4];
        mat b[4];

        //Seperate A and B into a[i],b[i]
#pragma omp parallel for private(j, k, inirow, inicol, temp2)
        for (i = 0; i < 8; i++) {
            if (i < 4) {
                IniMat(&a[i], dim / 2, dim / 2);
                inirow = (i < 2) * (dim / 2);
                inicol = (i % 2) * (dim / 2);
                for (j = inirow; j < inirow + (dim / 2); j++) {
                    for (k = inicol; k < inicol + (dim / 2); k++) {
                        a[i].mat[j - inirow][k - inicol] = A->mat[j][k];
                    }
                }
            } else {
                temp2 = i - 4;
                IniMat(&b[temp2], dim / 2, dim / 2);
                inirow = (temp2 < 2) * (dim / 2);
                inicol = (temp2 % 2) * (dim / 2);
                for (j = inirow; j < inirow + (dim / 2); j++) {
                    for (k = inicol; k < inicol + (dim / 2); k++) {
                        b[temp2].mat[j - inirow][k - inicol] = B->mat[j][k];
                    }
                }
            }
        }

        MnsMat(&b[1], &b[3], &s[0]);
        AddMat(&a[0], &a[1], &s[1]);
        AddMat(&a[2], &a[3], &s[2]);
        MnsMat(&b[2], &b[0], &s[3]);
        AddMat(&a[0], &a[3], &s[4]);
        AddMat(&b[0], &b[3], &s[5]);
        MnsMat(&a[1], &a[3], &s[6]);
        AddMat(&b[2], &b[3], &s[7]);
        MnsMat(&a[0], &a[2], &s[8]);
        AddMat(&b[0], &b[1], &s[9]);

        StrassenMulMat(&a[0], &s[0], &p[0]);
        StrassenMulMat(&s[1], &b[3], &p[1]);
        StrassenMulMat(&s[2], &b[0], &p[2]);
        StrassenMulMat(&a[3], &s[3], &p[3]);
        StrassenMulMat(&s[4], &s[5], &p[4]);
        StrassenMulMat(&s[6], &s[7], &p[5]);
        StrassenMulMat(&s[8], &s[9], &p[6]);


        //compute result matrix
        int semi_dim = dim / 2;
#pragma omp parallel for
        for (i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if ((i < semi_dim) & (j < semi_dim)) {
                    result->mat[i][j] = p[4].mat[i][j] + p[3].mat[i][j] - p[1].mat[i][j] + p[5].mat[i][j];
                } else if ((i >= semi_dim) & (j < semi_dim)) {
                    result->mat[i][j] = p[2].mat[i - semi_dim][j] + p[3].mat[i - semi_dim][j];
                } else if ((i >= semi_dim) & (j >= semi_dim)) {
                    result->mat[i][j] = p[4].mat[i - semi_dim][j - semi_dim] + p[0].mat[i - semi_dim][j - semi_dim] -
                                        p[2].mat[i - semi_dim][j - semi_dim] - p[6].mat[i - semi_dim][j - semi_dim];
                } else {
                    result->mat[i][j] = p[0].mat[i][j - semi_dim] + p[1].mat[i][j - semi_dim];
                }
            }
        }
    }
}