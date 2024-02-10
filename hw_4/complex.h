#ifndef COMPLEX
#define COMPLEX

#include <iostream>

class Complex {
    public:
    Complex(double x, double y) : re(x), im(y) {}
    Complex(double a) : re(a), im(0) {};

    double magnitude() const;

    double real() const;

    double imaginary() const;

    Complex conjugate() const;

    friend bool operator<(const Complex& a, const Complex& b);

    friend Complex operator*(const Complex& a, const Complex& b);

    friend Complex operator+(const Complex& a, const Complex& b);

    friend bool operator==(const Complex& a, const Complex& b);

    private:
    double re, im;
}; 



#endif