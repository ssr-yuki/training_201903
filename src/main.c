#include "main.h"

int main(void) {
    const Matrix A = {3, 3, (double*) A_data};
    const Matrix B = {3, 3, (double*) B_data};

    /*
    calcSum((Matrix*) &A, (Matrix*) &B);
    calcDifference((Matrix*) &A, (Matrix*) &B);
    calcProduct((Matrix*) &A, (Matrix*) &B);
    */

    printf("Det:\n\t%le\n", calcDeterminant((Matrix*) &A));
    
    return 0;
}

void calcSum(Matrix *A_ptr, Matrix *B_ptr) {
    unsigned int row = 0, column = 0;
    if(A_ptr->row == B_ptr->row && A_ptr->column == B_ptr->column) {
        row    = A_ptr->row;
        column = A_ptr->column;
    } else {
        printf("Not calculable: +");
        return;
    }

    double *C = (double*) malloc(sizeof(double) * row * column);
    printf("Sum:\n");
    for(int i = 0; i < row; i ++) {
        for(int j = 0; j < column; j++) {
            unsigned int index = i * column + j;
            C[index] = A_ptr->data[index] + B_ptr->data[index];
            printf("\t%le", C[index]);
        }
        printf("\n");
    }

    return;
}

void calcDifference(Matrix *A_ptr, Matrix *B_ptr) {
    unsigned int row = 0, column = 0;
    if(A_ptr->row == B_ptr->row && A_ptr->column == B_ptr->column) {
        row    = A_ptr->row;
        column = A_ptr->column;
    } else {
        printf("Not calculable: -");
        return;
    }

    double *C = (double*) malloc(sizeof(double) * row * column);
    printf("Difference:\n");
    for(int i = 0; i < row; i ++) {
        for(int j = 0; j < column; j++) {
            unsigned int index = i * column + j;
            C[index] = A_ptr->data[index] - B_ptr->data[index];
            printf("\t%le", C[index]);
        }
        printf("\n");
    }

    return;
}

void calcProduct(Matrix *A_ptr, Matrix *B_ptr) {
    unsigned int row = 0, column = 0;
    if(A_ptr->column == B_ptr->row) {
        row    = A_ptr->row;
        column = B_ptr->column;
    } else {
        printf("Not calculable: *");
        return;
    }

    double *C = (double*) malloc(sizeof(double) * row * column);
    printf("Product:\n");
    for(int i = 0; i < row; i ++) {
        for(int j = 0; j < column; j++) {
            unsigned int index = i * column + j;
            C[index] = 0.0;

            for(int k = 0; k < A_ptr->column; k++) {
                C[index] += A_ptr->data[i * A_ptr->column + k] * B_ptr->data[k * B_ptr->column + j];
            }

            printf("\t%le", C[index]);
        }
        printf("\n");
    }

    return;
}

double calcDeterminant(Matrix *A_ptr) {
    if(A_ptr->row != A_ptr->column) {
        printf("Not calculable: Inverse");
        return NAN;
    }

    unsigned int n = A_ptr->row;
    
    double det = 0.0;
    
    if(n > 1) {
        for(int i = 0; i < n; i++) {
            double tmp_data[n - 1][n - 1];

            for(int j = 0; j < n - 1; j++) {
                for(int k = 0; k < n; k++) {
                    if(k < i) {
                        tmp_data[j][k] = A_ptr->data[(j + 1) * n + k];
                    } else if(k > i) {
                        tmp_data[j][k - 1] = A_ptr->data[(j + 1) * n + k];
                    }
                }
            }

            Matrix tmp_matrix = {n - 1, n - 1, (double*) &tmp_data};
            double cofactor = calcDeterminant(&tmp_matrix);
            if(i % 2 == 1) {
                cofactor *= -1.0;
            }

            det += A_ptr->data[i] * cofactor;
        }
    } else if(n == 1) {
        det = A_ptr->data[0];
    }

    return det;
}
