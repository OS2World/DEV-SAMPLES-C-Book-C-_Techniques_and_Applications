//  Module:     Wdw_Copy  (Window Class)
//  Version:    2.11
//
//  Language:   C++ 2.0
//  Environ:    IBM-PC MS-DOS
//
//  Purpose:    Copy constructor / assignment operator
//
//  Written by: Scott Robert Ladd

#include "Str.hpp"
#include "Window.hpp"

extern "C"
    {
    #include "string.h"
    #include "stdio.h"
    #include "stddef.h"
    #include "dos.h"
    }

// copy constructor
Window::Window(const Window & w) : Header(w.Header)
    {
    // duplicate instance variables
    HomeLine = w.HomeLine;
    HomeCol  = w.HomeCol;
    Length   = w.Length;
    Width    = w.Width;
    CrsLine  = w.CrsLine;
    CrsCol   = w.CrsCol;

    InsideColor = w.InsideColor;
    BorderColor = w.BorderColor;

    Border = w.Border;

    Wrapped   = w.Wrapped;
    Concealed = w.Concealed;

    // allocate a buffer

    BufferSW = new WindowWord [Length * Width];

    if (BufferSW == NULL)
        ErrorHandler();

    // copy existing buffer into new buffer
    for (unsigned int l = 0; l < Length; ++l)
        {
        for (unsigned int c = 0; c < Width; ++c)
            BufferSW[l * Width + c] = w.BufferSW[l * Width + c];
        }

    // add window to list
    WdwList.Store(this);

    // make this the top window
    TopWindow = this;

    // plot what it owns
    PlotOwnership();

    // display it
    Paint();
    }

// assignment operator
void Window::operator = (const Window & w)
    {
    // free old buffer
    delete BufferSW;

    // copy instance variables
    HomeLine = w.HomeLine;
    HomeCol  = w.HomeCol;
    Length   = w.Length;
    Width    = w.Width;
    CrsLine  = w.CrsLine;
    CrsCol   = w.CrsCol;

    InsideColor = w.InsideColor;
    BorderColor = w.BorderColor;

    Border = w.Border;

    Wrapped   = w.Wrapped;
    Concealed = w.Concealed;

    Header = w.Header;

    // allocate new buffer
    BufferSW = new WindowWord [Length * Width];

    if (BufferSW == NULL)
        ErrorHandler();

    // copy buffer from existing window
    for (unsigned int l = 0; l < Length; ++l)
        {
        for (unsigned int c = 0; c < Width; ++c)
            BufferSW[l * Width + c] = w.BufferSW[l * Width + c];
        }

    // plot what this window owns
    PlotOwnership();

    // paint all windows
    Restack();
    }
