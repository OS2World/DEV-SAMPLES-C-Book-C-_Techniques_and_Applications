//  Module:     Cp_Misc
//  Version:    2.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Miscellaneous methods for Complex class
//
//  Written by: Scott Robert Ladd

#include "Complex.hpp"

extern "C"
    {
    #include "math.h"
    #include "stdio.h"
    #include "stdlib.h"
    }

// polar coordinate methods
Complex polar(const double radius, const double theta)
    {
    Complex result;

    result.Real = radius * cos(theta);
    result.Imag = radius * sin(theta);

    return result;
    }

Complex conj(const Complex & c)
    {
    Complex result;

    result.Real =  c.Real;
    result.Imag = -c.Imag;

    return result;
    }

// output method
int Complex::Print() const
    {
    int out_len;

    out_len = printf("(%g", Real);

    if (Imag >= 0.0)
        {
        ++out_len;
        putchar('+');
        }

    out_len += printf("%g)", Imag);

    return out_len;
    }
