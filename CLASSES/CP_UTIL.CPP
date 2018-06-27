//  Module:     Cp_Util
//  Version:    2.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Utility methods for Complex class
//
//  Written by: Scott Robert Ladd

#include "Complex.hpp"

extern "C"
    {
    #include "math.h"
    #include "stdio.h"
    #include "stdlib.h"
    }

// prototype for default error handler
static void DefaultHandler();

// assignment of default handler address to error function pointer
void (* Complex::ErrorHandler)() = DefaultHandler;

// default error handler
static void DefaultHandler()
    {
    puts("\aERROR in complex object: DIVIDE BY ZERO\n");
    exit(1);
    }

// constructors
Complex::Complex (void)
    {
    Real = 0.0;
    Imag = 0.0;
    }

Complex::Complex (const Complex & c)
    {
    Real = c.Real;
    Imag = c.Imag;
    }

Complex::Complex (const double & r, const double & i)
    {
    Real = r;
    Imag = i;
    }

Complex::Complex (const double & r)
    {
    Real = r;
    Imag = 0.0;
    }

// method to set error handler function
void Complex::SetErrorHandler(void (* userHandler)())
    {
    ErrorHandler = userHandler;
    }

// value extraction methods
double real (const Complex & c)
    {
    return c.Real;
    }

double imag (const Complex & c)
    {
    return c.Imag;
    }

// assignment method
void Complex::operator = (const Complex & c)
    {
    Real = c.Real;
    Imag = c.Imag;
    }

// utility methods
double abs(const Complex & c)
    {
    double result = sqrt(c.Real * c.Real + c.Imag * c.Imag);

    return result;
    }

double norm(const Complex & c)
    {
    double result = (c.Real * c.Real) + (c.Imag * c.Imag);

    return result;
    }

double arg(const Complex & c)
    {
    double result = atan2(c.Imag, c.Real);

    return result;
    }
