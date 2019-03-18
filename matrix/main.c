#include "main.h"

int main(void) {
    const Matrix A = {3, 3, (double*) A_data};
    const Matrix B = {3, 3, (double*) B_data};

    calcSum((Matrix*) &A, (Matrix*) &B);
    calcDifference((Matrix*) &A, (Matrix*) &B);
    calcProduct((Matrix*) &A, (Matrix*) &B);
    calcInverse((Matrix*) &A);
    
    return 0;
}

void calcSum(Matrix *A_ptr, Matrix *B_ptr) {
    unsigned int row = 0, column = 0;
    if(A_ptr->row == B_ptr->row && A_ptr->column == B_ptr->column) {
        row    = A_ptr->row;
        column = A_ptr->column;
    } else {
        printf("Not calculable: +\n");
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

    free(C);

    return;
}

void calcDifference(Matrix *A_ptr, Matrix *B_ptr) {
    unsigned int row = 0, column = 0;
    if(A_ptr->row == B_ptr->row && A_ptr->column == B_ptr->column) {
        row    = A_ptr->row;
        column = A_ptr->column;
    } else {
        printf("Not calculable: -\n");
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

    free(C);

    return;
}

void calcProduct(Matrix *A_ptr, Matrix *B_ptr) {
    unsigned int row = 0, column = 0;
    if(A_ptr->column == B_ptr->row) {
        row    = A_ptr->row;
        column = B_ptr->column;
    } else {
        printf("Not calculable: *\n");
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

    free(C);

    return;
}

double calcCofactor(Matrix* A_ptr, unsigned int row_index, unsigned int column_index) {
    if(A_ptr->row != A_ptr->column) {
        printf("Not calculable: Cofactor\n");
        return NAN;
    } else if(row_index > A_ptr->row || column_index > A_ptr->column
            || row_index * column_index == 0) {
        printf("Index Error on Calculating a Cofactor\n");
        return NAN;
    }

    unsigned int n = A_ptr->row;
    double       tmp_data[n - 1][n - 1];

    for(int j = 0; j < n; j++) {
        if(j < row_index - 1) {
            for(int k = 0; k < n; k++) {
                if(k < column_index - 1) {
                    tmp_data[j][k] = A_ptr->data[j * n + k];
                } else if(k > column_index - 1) {
                    tmp_data[j][k - 1] = A_ptr->data[j * n + k];
                }
            }
        } else if(j > row_index - 1) {
            for(int k = 0; k < n; k++) {
                if(k < column_index - 1) {
                    tmp_data[j - 1][k] = A_ptr->data[j * n + k];
                } else if(k > column_index - 1) {
                    tmp_data[j - 1][k - 1] = A_ptr->data[j * n + k];
                }
            }
        }
    }

    Matrix tmp_matrix = {n - 1, n - 1, (double*) &tmp_data};

    double sign;
    if((row_index + column_index) % 2 == 0) {
        sign =  1.0;
    } else {
        sign = -1.0;
    }

    double ret = sign * calcDeterminant((Matrix*) &tmp_matrix);
    return ret;
}

double calcDeterminant(Matrix *A_ptr) {
    if(A_ptr->row != A_ptr->column) {
        printf("Not calculable: Determinant\n");
        return NAN;
    }

    unsigned int n = A_ptr->row;
    
    double det = 0.0;
    
    if(n > 1) {
        for(int i = 0; i < n; i++) {
            double cofactor = calcCofactor(A_ptr, 1, i + 1);

           det += A_ptr->data[i] * cofactor;
        }
    } else if(n == 1) {
        det = A_ptr->data[0];
    }

    return det;
}

void calcInverse(Matrix* A_ptr) {
    if(A_ptr->row != A_ptr->column) {
        printf("Not calculable: Inverse\n");
        return;
    }

    double det = calcDeterminant(A_ptr);
    printf("Determinant:\n\t%le\n", det);
    if(det == 0.0) {
        printf("Inverse Matrix does not exist\n");
        return;
    }

    unsigned int n = A_ptr->row;

    double *C = (double*) malloc(sizeof(double) * n * n);

    printf("Inverse:\n");

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            C[i * n + j] = calcCofactor(A_ptr, (j + 1), i + 1) / det;

            printf("\t%le", C[i * n + j]);
        }
        printf("\n");
    }

    free(C);

    return;
}

