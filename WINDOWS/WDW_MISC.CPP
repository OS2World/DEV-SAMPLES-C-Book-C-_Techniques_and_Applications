//  Module:     Wdw_Misc  (Window Class)
//  Version:    2.11
//
//  Language:   C++ 2.0
//  Environ:    IBM-PC MS-DOS
//
//  Purpose:    Miscellaneous methods
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

// change position
void Window::Move(unsigned int line, unsigned int col)
    {
    if ((line > MaxLength) || (col > MaxWidth))
        return;

    // set new window position
    HomeLine = line;
    HomeCol  = col;

    // redisplay all windows
    Restack();
    }

// make this the top window
void Window::Hoist()
    {
    // delete window from list
    WdwList.Delete(this);

    // add it to the list (making it the top window)!
    WdwList.Store(this);

    TopWindow = this;

    // redisplay all windows
    Restack();
    }

// conceal this window
void Window::Conceal()
    {
    Concealed = 0;

    Restack();
    }

// reveal this window
void Window::Reveal()
    {
    Concealed = 0;

    Restack();
    }

// turn wrap on
void Window::WrapOn()
    {
    Wrapped = 1;
    }

// turn wrap off
void Window::WrapOff()
    {
    Wrapped = 0;
    }

// set the heading
void Window::SetHead(String & heading)
    {
    if (Border == BT_NONE)
        return;

    unsigned int c, hpos;
    char bordchar;

    // pick border characater
    if (Border == BT_SINGLE)
        bordchar = 0xC4;
    else
        bordchar = 0xCD;

    Header = heading;

    // no header, fill in border
    if (Header.Length() == 0)
        {
        for (c = 0; c < Width; ++c)
            Display(-1,c,BorderColor,bordchar);

        return;
        }

    hpos = 0;

    // display header and border fragment
    for (c = 0; c < Width; ++c)
        if (hpos < Header.Length())
            {
            Display(-1,c,BorderColor,Header[hpos]);
            ++hpos;
            }
        else
            Display(-1,c,BorderColor,bordchar);
    }

// set the cursor position
void Window::SetCursor(unsigned int line, unsigned int col)
    {
    // cursor can only be positioned within top window
    if ((line > Length) || (col > Width) || (this != TopWindow))
        return;

    unsigned char newl = line + HomeLine;
    unsigned char newc = col  + HomeCol;

    if ((newl > MaxLength) || (newc > MaxWidth))
        return;

    CrsLine = line;
    CrsCol  = col;

    // physically set cursor position
    Screen::CursorSetPos(newl, newc);
    }

// get the cursor position
void Window::GetCursor(unsigned int & line, unsigned int & col)
    {
    line = CrsLine;
    col  = CrsCol;
    }

// clear the entire window
void Window::ClearAll()
    {
    unsigned int pos = 0;

    for (unsigned char l = 0; l < Length; ++l)
        {
        for (unsigned char c = 0; c < Width; ++c)
            {
            BufferSW[pos].Symbol    = ' ';
            BufferSW[pos].Attribute = InsideColor;

            ++pos;
            }
        }
    }

// clear one line of the window
void Window::ClearLine(unsigned int line, unsigned int col)
    {
    unsigned int pos;

    for (unsigned char c = col; c < Width; ++c)
        {
        pos = line * Width + c;

        BufferSW[pos].Symbol    = ' ';
        BufferSW[pos].Attribute = InsideColor;
        }
    }
