//
// Created by 吕文韬 on 2021/10/16.
//

#ifndef CMAT__BASIC_CALCULATE__H
#define CMAT__BASIC_CALCULATE__H

#include "../cmat.h"

void AddMat(mat *A, mat *B, mat *result);

int _Min(int a, int b, int c, int d);

void NmMulMat(mat *A, mat *B, mat *result);

void MnsMat(mat *A, mat *B, mat *result);

void StrassenMulMat(mat *A, mat *B, mat *result);

#endif //CMAT__BASIC_CALCULATE__H
