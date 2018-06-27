//  Module:     Cp_trig
//  Version:    2.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Trignometric functions for Complex class
//
//  Written by: Scott Robert Ladd

#include "Complex.hpp"

extern "C"
    {
    #include "math.h"
    #include "stdlib.h"
    }

// trigonometric methods
Complex cos(const Complex & c)
    {
    Complex result;

    result.Real =  cos(c.Real) * cosh(c.Imag);
    result.Imag = -sin(c.Real) * sinh(c.Imag);

    return result;
    }

Complex sin(const Complex & c)
    {
    Complex result;

    result.Real = sin(c.Real) * cosh(c.Imag);
    result.Imag = cos(c.Real) * sinh(c.Imag);

    return result;
    }

Complex tan(const Complex & c)
    {
    Complex result = sin(c) / cos(c);

    return result;
    }

Complex cosh(const Complex & c)
    {
    Complex result;

    result.Real = cos(c.Imag) * cosh(c.Real);
    result.Imag = sin(c.Imag) * sinh(c.Real);

    return result;
    }

Complex sinh(const Complex & c)
    {
    Complex result;

    result.Real = cos(c.Imag) * sinh(c.Real);
    result.Imag = sin(c.Imag) * cosh(c.Real);

    return result;
    }

Complex tanh(const Complex & c)
    {
    Complex result = sinh(c) / cosh(c);

    return result;
    }
