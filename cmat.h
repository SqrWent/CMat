#ifndef CMAT_CMAT_H
#define CMAT_CMAT_H

typedef struct {
    int row;
    int col;
    double _Complex **mat;
} mat;

void IniMat(mat *A, int row, int col);

void FreMat(mat *A);

void TraMat(mat *A, mat *result);

void CojMat(mat *A, mat *result);

void ZeroMat(mat *A);

void ZIniMat(mat *A, int row, int col);

void IIniMat(mat *A, int dim);

void AddMat(mat *A, mat *B, mat *result);

int _Min(int a, int b, int c, int d);

void NmMulMat(mat *A, mat *B, mat *result);

void MnsMat(mat *A, mat *B, mat *result);

void StrassenMulMat(mat *A, mat *B, mat *result);

#endif //CMAT_CMAT_H