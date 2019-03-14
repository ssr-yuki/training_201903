#ifndef TRAINING_MAIN_H
#define TRAINING_MAIN_H

#include <stdio.h>
#include <stdlib.h>

#include "constant.h"

typedef struct matrix {
    unsigned int row;
    unsigned int column;
    double*      data;
} Matrix;

void calcSum(Matrix*, Matrix*);
void calcDifference(Matrix*, Matrix*);
void calcProduct(Matrix*, Matrix*);
double calcDeterminant(double*, int);
double calcInverse(double*, int);



#endif

