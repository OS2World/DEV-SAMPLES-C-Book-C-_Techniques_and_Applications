//  Module:     Containr (Abstract Base Class for Containers)
//  Version:    3.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides an abstract base class for container classes.
//
//  Written by: Scott Robert Ladd

#include "Containr.hpp"

extern "C"
    {
    #include "stdio.h"
    }

// prototypes
static void DefaultHandler();

// default exception handler
static void DefaultHandler()
    {
    puts("\aContainer Error: memory allocation failure!");
    }

// constructor
Container::Container()
    {
    Count = 0;
    ErrorHandler = DefaultHandler;
    }

// copy constructor
Container::Container(const Container & c)
    {
    Count = c.Count;
    ErrorHandler = c.ErrorHandler;
    }

// assignment opeartor
void Container::operator = (const Container & c)
    {
    Count = c.Count;
    ErrorHandler = c.ErrorHandler;
    }
