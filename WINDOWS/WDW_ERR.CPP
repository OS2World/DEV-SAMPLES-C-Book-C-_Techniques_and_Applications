//  Module:     Wdw_Err  (Window Class main routines)
//  Version:    2.11
//
//  Language:   C++ 2.0
//  Environ:    IBM-PC MS-DOS
//
//  Purpose:    Error handler and first-time initialization
//
//  Written by: Scott Robert Ladd

#include "Screen.hpp"
#include "Window.hpp"

extern "C"
    {
    #include "stdio.h"
    #include "stdlib.h"
    }

// internal prototype
static void DefaultHandler();

void (* Window::ErrorHandler)() = DefaultHandler;

// default exception handler
static void DefaultHandler()
    {
    puts("\aWindow Error: allocation failure\n");
    }

// assign an exception handler
void Window::SetErrorHandler(void (* userHandler)())
    {
    ErrorHandler = userHandler;
    }

// first time initialization function
void Window::FirstTime()
    {
    Initialized = 1;

    // obtain screen dimensions
    Screen::Dimensions(MaxWidth, MaxLength);

    unsigned int area = MaxLength * MaxWidth;

    // using malloc due to bug in cfront
    ScrnOwner = (Window **)malloc(area * sizeof(Window *));

    if (ScrnOwner == NULL)
        ErrorHandler();

    // clear the ownership array
    for (unsigned int l = 0; l < MaxLength; ++l)
        {
        for (unsigned int c = 0; c < MaxWidth; ++c)
            ScrnOwner[l * MaxWidth + c] = NULL;
        }
    }
