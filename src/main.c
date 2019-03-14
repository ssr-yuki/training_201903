#include "main.h"

int main(void) {
    const Matrix A = {3, 3, (double*) A_data};
    const Matrix B = {3, 3, (double*) B_data};

    calcSum((Matrix*) &A, (Matrix*) &B);
    calcDifference((Matrix*) &A, (Matrix*) &B);
    calcProduct((Matrix*) &A, (Matrix*) &B);
    
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
        printf("Not calculable: +");
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




