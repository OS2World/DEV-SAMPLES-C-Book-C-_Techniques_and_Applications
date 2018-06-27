//  Module:     Cp_comp
//  Version:    2.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Comparison operations for Complex class
//
//  Written by: Scott Robert Ladd

#include "Complex.hpp"

extern "C"
    {
    #include "math.h"
    #include "stdlib.h"
    }

// comparison methods
int operator == (const Complex & c1, const Complex & c2)
    {
    return (c1.Real == c2.Real) && (c1.Imag == c2.Imag);
    }

int operator != (const Complex & c1, const Complex & c2)
    {
    return (c1.Real != c2.Real) || (c1.Imag != c2.Imag);
    }


int operator <  (const Complex & c1, const Complex & c2)
    {
    return abs(c1) < abs(c2);
    }

int operator <= (const Complex & c1, const Complex & c2)
    {
    return abs(c1) <= abs(c2);
    }


int operator >  (const Complex & c1, const Complex & c2)
    {
    return abs(c1) > abs(c2);
    }

int operator >= (const Complex & c1, const Complex & c2)
    {
    return abs(c1) >= abs(c2);
    }
