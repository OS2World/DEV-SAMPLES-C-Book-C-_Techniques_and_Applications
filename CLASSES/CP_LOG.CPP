//  Module:     Cp_log
//  Version:    2.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Logarithmic functions for Complex class
//
//  Written by: Scott Robert Ladd

#include "Complex.hpp"

extern "C"
    {
    #include "math.h"
    #include "stdlib.h"
    }

// logarithmic methods
Complex exp(const Complex & c)
    {
    double X = exp(c.Real);

    Complex result;

    result.Real = X * cos(c.Imag);
    result.Imag = X * sin(c.Imag);

    return result;
    }

Complex log(const Complex & c)
    {
    double hypot = abs(c);

    Complex result;

    if (hypot > 0.0)
        {
        result.Real = log(hypot);
        result.Imag = atan2(c.Imag, c.Real);
        }
    else
        Complex::ErrorHandler();

    return result;
    }
