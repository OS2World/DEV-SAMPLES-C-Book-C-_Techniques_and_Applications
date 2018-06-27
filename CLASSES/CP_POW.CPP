//  Module:     Cp_Pow
//  Version:    2.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Power function for Complex class
//
//  Written by: Scott Robert Ladd

#include "Complex.hpp"

extern "C"
    {
    #include "math.h"
    #include "stdlib.h"
    }

// "power" methods
Complex pow(const Complex & c, const Complex & power)
    {
    Complex result;

    if (power.Real == 0.0 && power.Imag == 0.0)
        {
        result.Real = 1.0;
        result.Imag = 0.0;
        }
    else
        {
        if (c.Real != 0.0 || c.Imag != 0.0)
            result = exp(log(c) * power);
        else
            Complex::ErrorHandler();
        }

    return result;
    }

Complex sqrt(const Complex & c)
    {
    return pow(c,Complex(0.5,0.0));
    }
