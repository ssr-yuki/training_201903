#ifndef RUNGE_KUTTA_METHOD_H
#define RUNGE_KUTTA_METHOD_H

#include <stdio.h>

// constants
// model: m x'' = - k x - c x'.
double m = 1.0, c = 2.0, k = 10.0;
double h = 0.01;

double updateVelocity(double, double);
double updatePosition(double, double);

#endif


