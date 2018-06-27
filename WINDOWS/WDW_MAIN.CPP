//  Module:     Wdw_Main  (Window Class main routines)
//  Version:    2.11
//
//  Language:   C++ 2.0
//  Environ:    IBM-PC MS-DOS
//
//  Purpose:    Static member initialization, utility functions and other.
//
//  Written by: Scott Robert Ladd

#include "Screen.hpp"
#include "Str.hpp"
#include "Window.hpp"

extern "C"
    {
    #include "string.h"
    #include "stddef.h"
    #include "dos.h"
    }

// internal prototype
static void DefaultHandler();

// initialize static class members!

WorkList     Window::WdwList;

Window **    Window::ScrnOwner   = NULL;
int          Window::Initialized = 0;
Window *     Window::TopWindow   = NULL;
unsigned int Window::MaxLength   = 0;
unsigned int Window::MaxWidth    = 0;


// actually display a character
void Window::Display(int line, int col,
                     unsigned char attr, char ch)
    {
    unsigned int rl = line + HomeLine;
    unsigned int rc = col  + HomeCol;

    if ((rl >= MaxLength) || (rc >= MaxWidth))
        return;

    if (this == ScrnOwner[rl * MaxWidth + rc])
        Screen::PutChar(rl,rc,attr,ch);
    }

// restack all windows
void Window::Restack()
    {
    Screen::Clear();

    // clear screen ownership grid
    for (unsigned int l = 0; l < MaxLength; ++l)
        {
        for (unsigned int c = 0; c < MaxWidth; ++c)
            ScrnOwner[l * MaxWidth + c] = NULL;
        }


    // start with the "lowest" window in the list
    WdwList.GoToTail();

    Window * curWdw = (Window *)WdwList.Examine();

    while (curWdw != NULL)
        {
        // plot what a Window owns
        curWdw->PlotOwnership();

        // the paint it
        curWdw->Paint();

        // get the next window
        WdwList.GoPrev();

        curWdw = (Window *)WdwList.Examine();
        }
    }

// plot which screen locations belong to this window
void Window::PlotOwnership()
    {
    unsigned int l, c;

    if (Concealed)
        return;

    // mark locations own by display area of window
    if ((Length == MaxLength) && (Width == MaxWidth))
        {
        for (l = 0; l < Length; ++l)
            for (c = 0; c < Width; ++c)
                ScrnOwner[l * MaxWidth + c] = this;
        }
    else
        {
        for (l = HomeLine; l < HomeLine + Length; ++l)
             for (c = HomeCol; c < HomeCol + Width; ++c)
                 if ((l < MaxLength) && (c < MaxWidth))
                     ScrnOwner[l * MaxWidth + c] = this;
        }

    // mark border locations
    if (Border != BT_NONE)
        {
        if (HomeCol > 0)
            {
            if (HomeLine > 0)
                ScrnOwner[(HomeLine - 1) * MaxWidth + (HomeCol - 1)] = this;

            if (Length < MaxLength)
                ScrnOwner[(Length + HomeLine) * MaxWidth + (HomeCol - 1)] = this;
            }

        if (Width < MaxWidth)
            {
            if (HomeLine > 0)
                ScrnOwner[(HomeLine - 1) * MaxWidth + (Width + HomeCol)] = this;

            if (Length < MaxLength)
                ScrnOwner[(Length + HomeLine) * MaxWidth + (Width + HomeCol)] = this;
            }

        if ((HomeLine + Length) < MaxLength)
            {
            for (c = HomeCol; c <= HomeCol + Width; ++c)
                ScrnOwner[(Length + HomeLine) * MaxWidth + c] = this;
            }

        if (HomeLine > 0)
            {
            for (c = HomeCol; c <= HomeCol + Width; ++c)
                ScrnOwner[(HomeLine - 1) * MaxWidth + c] = this;
            }

        if ((HomeCol + Width) < MaxWidth)
            {
            for (l = HomeLine; l <= HomeLine + Length; ++l)
                ScrnOwner[l * MaxWidth + Width + HomeCol] = this;
            }

        if (HomeCol > 0)
            {
            for (l = HomeLine; l <= HomeLine + Length; ++l)
                ScrnOwner[l * MaxWidth + HomeCol - 1] = this;
            }
        }
    }
