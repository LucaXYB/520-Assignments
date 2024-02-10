#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

double Complex::real() const {

    return re;

}

double Complex::imaginary() const {

    return im;

}

Complex Complex::conjugate() const {

    return Complex(re, -im);

}

Complex operator*(const Complex& a, const Complex& b) {
    
    return Complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);

}

Complex operator+(const Complex& a, const Complex& b) {

    return Complex(a.re + b.re, a.im + b.im);

}

bool operator==(const Complex& a, const Complex& b) {

    return a.re == b.re && a.im == b.im;

}