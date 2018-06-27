//  Module:     Cp_ops
//  Version:    2.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Basic operators for Complex objects
//
//  Written by: Scott Robert Ladd

#include "Complex.hpp"

extern "C"
    {
    #include "math.h"
    }

// unary minus method
Complex Complex::operator - ()
    {
    Complex result;

    result.Real = -Real;
    result.Imag = -Imag;

    return result;
    }

// calculation methods
Complex operator + (const Complex & c1, const Complex & c2)
    {
    Complex result;

    result.Real = c1.Real + c2.Real;
    result.Imag = c1.Imag + c2.Imag;

    return result;
    }

Complex operator - (const Complex & c1, const Complex & c2)
    {
    Complex result;

    result.Real = c1.Real - c2.Real;
    result.Imag = c1.Imag - c2.Imag;

    return result;
    }

Complex operator * (const Complex & c1, const Complex & c2)
    {
    Complex result;

    result.Real = (c1.Real * c2.Real) - (c1.Imag * c2.Imag);
    result.Imag = (c1.Real * c2.Imag) + (c1.Imag * c2.Real);

    return result;
    }

Complex operator / (const Complex & c1, const Complex & c2)
    {
    Complex result;
    double den;

    den = norm(c2);

    if (den != 0.0)
        {
        result.Real = (c1.Real * c2.Real + c1.Imag * c2.Imag) / den;
        result.Imag = (c1.Imag * c2.Real - c1.Real * c2.Imag) / den;
        }
    else
        Complex::ErrorHandler();

    return result;
    }
