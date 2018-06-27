//  Module:     Cp_asop
//  Version:    2.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Assignment operators for Complex objects
//
//  Written by: Scott Robert Ladd

#include "Complex.hpp"

Complex Complex::operator += (const Complex & c)
    {
    Real += c.Real;
    Imag += c.Imag;

    return *this;
    }

Complex Complex::operator -= (const Complex & c)
    {
    Real -= c.Real;
    Imag -= c.Imag;

    return *this;
    }

Complex Complex::operator *= (const Complex & c)
    {
    double OldReal = Real; // save old Real value

    Real = (Real * c.Real) - (Imag * c.Imag);
    Imag = (OldReal * c.Imag) + (Imag * c.Real);

    return *this;
    }

Complex Complex::operator /= (const Complex & c)
    {
    double den = norm(c);

    if (den != 0.0)
        {
        double OldReal = Real;

        Real = (Real * c.Real + Imag * c.Imag) / den;
        Imag = (Imag * c.Real - OldReal * c.Imag) / den;
        }
    else
        Complex::ErrorHandler();

    return *this;
    }
