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

#endif //CMAT_CMAT_H