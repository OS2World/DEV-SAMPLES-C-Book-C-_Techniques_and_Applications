//  Module:     Wdw_Disp  (Window Class)
//  Version:    2.11
//
//  Language:   C++ 2.0
//  Environ:    IBM-PC MS-DOS
//
//  Purpose:    Display methods
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

// paint entire window
void Window::Paint()
    {
    if (Concealed)
        return;

    unsigned int l, c, hpos;

    // draw border
    switch (Border)
        {
        case BT_SINGLE :
            Display(-1,-1,BorderColor,'\xDA');
            Display(Length,-1,BorderColor,'\xC0');
            Display(Length,Width,BorderColor,'\xD9');
            Display(-1,Width,BorderColor,'\xBF');

            if (Header.Length() == 0)
                for (c = 0; c < Width; ++c)
                    {
                    Display(-1,c,BorderColor,'\xC4');
                    Display(Length,c,BorderColor,'\xC4');
                    }
            else
                {
                hpos = 0;

                for (c = 0; c < Width; ++c)
                    {
                    if (hpos < Header.Length())
                        {
                        Display(-1,c,BorderColor,Header[hpos]);
                        ++hpos;
                        }
                    else
                        Display(-1,c,BorderColor,'\xC4');

                    Display(Length,c,BorderColor,'\xC4');
                    }
                }

            for (l = 0; l < Length; ++l)
                {
                Display(l,-1,BorderColor,'\xB3');
                Display(l,Width,BorderColor,'\xB3');
                }

            break;

        case BT_DOUBLE :
            Display(-1,-1,BorderColor,'\xC9');
            Display(Length,-1,BorderColor,'\xC8');
            Display(Length,Width,BorderColor,'\xBC');
            Display(-1,Width,BorderColor,'\xBB');

            if (Header.Length() == 0)
                for (c = 0; c < Width; ++c)
                    {
                    Display(-1,c,BorderColor,'\xCD');
                    Display(Length,c,BorderColor,'\xCD');
                    }
            else
                {
                hpos = 0;

                for (c = 0; c < Width; ++c)
                    {
                    if (hpos < Header.Length())
                        {
                        Display(-1,c,BorderColor,Header[hpos]);
                        ++hpos;
                        }
                    else
                        Display(-1,c,BorderColor,'\xCD');

                    Display(Length,c,BorderColor,'\xCD');
                    }
                }

            for (l = 0; l < Length; ++l)
                {
                Display(l,-1,BorderColor,'\xBA');
                Display(l,Width,BorderColor,'\xBA');
                }
        }

    unsigned int pos;

    // display each character in buffer
    for (l = 0; l < Length; ++l)
        for (c = 0; c < Width; ++c)
            {
            pos = l * Width + c;
            Display(l, c, BufferSW[pos].Attribute, BufferSW[pos].Symbol);
            }

    // set the cursor position
    SetCursor(CrsLine, CrsCol);
    }

// paint one line
void Window::PaintLine(unsigned int line)
    {
    if ((Concealed) || (line > Length))
        return;

    unsigned int pos;

    // draw just one line of contents
    for (unsigned int c = 0; c < Width; ++c)
        {
        pos = line * Width + c;
        Display(line, c, BufferSW[pos].Attribute, BufferSW[pos].Symbol);
        }
    }

// store a character in the window
void Window::PutChar(unsigned int line, unsigned int col,
                     unsigned char attr, char ch)
    {
    if ((line >= Length) || (col >= Width))
        return;

    unsigned int pos = line * Width + col;

    // store the character...
    BufferSW[pos].Symbol = ch;

    // ... and its attribute
    if (attr != 0)
        BufferSW[pos].Attribute = attr;
    else
        BufferSW[pos].Attribute = InsideColor;
    }

// store a string in the window
void Window::PutStr(unsigned int line, unsigned int col,
                    unsigned char attr, String & s)
    {
    if ((line >= Length) || (col >= Width))
        return;

    if (attr == 0)
        attr = InsideColor;

    unsigned char l = line;
    unsigned char c = col;
   
    unsigned int spos = 0;
    unsigned int wpos;

    // display text
    while (s[spos] != '\x00')
        {
        wpos = l * Width + c;

        BufferSW[wpos].Symbol    = s[spos];
        BufferSW[wpos].Attribute = attr;

        if (c == (Width - 1))
            {
            if (!Wrapped)
                return;

            if (l < Length)
                {
                c = 0;
                ++l;
                }
            else
                return;
            }
        else
            ++c;

        ++spos;
        }
    }
