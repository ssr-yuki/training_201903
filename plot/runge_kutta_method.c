#include "runge_kutta_method.h"

int main(void) {
    double x = 4.0, dx = -7.0;
    double t = 0.0;

    do {
        printf("%lf\t%lf\t%lf\n", t, x ,dx);
        dx = updateVelocity(x, dx);
        x  = updatePosition(x, dx);
        t += h;
    } while(t < 10.0);
    
    return 0;
}

double calcAcceleration(double x, double v) {
    return (- k * x - c * v) / m;
}

double updateVelocity(double x, double v_previous) {
    double v_next;
    double k1 = calcAcceleration(x, v_previous);
    double k2 = calcAcceleration(x, v_previous + h * k1 / 2);
    double k3 = calcAcceleration(x, v_previous + h * k2 / 2);
    double k4 = calcAcceleration(x, v_previous + h * k3);
    
    v_next = v_previous + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);

    return v_next;
}

double updatePosition(double x_previous, double v) {
    return x_previous + h * v;
}


