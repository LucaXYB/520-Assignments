#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
    double real;
    double im;
} Complex;

Complex add(Complex a, Complex b);
Complex negate(Complex a);
Complex multiply(Complex a, Complex b);
double magnitude(Complex a);

#endif

