//  Header:     Screen  (MS-DOS Text Video Display Class)
//  Version:    1.10
//
//  Language:   C++ 2.0
//  Environ:    MS-DOS w/monochrome or color text display
//
//  Purpose:    Provides a class for manipulating a text display.
//
//  WARNING!    To drastically improve the speed of this class, NO RANGE
//              CHECKING is done! Invalid line/column values may cause
//              portions of non-video memory to be corrupted!
//
//  Written by: Scott Robert Ladd

#if !defined(__SCREEN_HPP)
#define __SCREEN_HPP 1

#include "Str.hpp"

extern "C"
    {
    #include "peekpoke.h"
    #include "stddef.h"
    }

enum BoxType {BT_NONE, BT_SINGLE, BT_DOUBLE, BT_SOLID};

class Screen
    {
    protected:
        static unsigned int  Width;        // width of the screen in characters
        static unsigned int  Length;       // length of the screen in characters

        static unsigned int  BaseAdr;      // base address of character memory

        static unsigned int  CursorShape;  // stored shape of the cursor
        static int           CursorHidden; // non-zero if cursor has been hidden

        static unsigned int  HowMany;      // How many screens instantiated?

    public:
        // constructor
        Screen();

        // destructor
        ~Screen();

        // retrieve screen size method
        static void Dimensions(unsigned int & wid, unsigned int & len);

        // cursor methods
        static void CursorHide();
        static void CursorUnhide();

        static void CursorSetPos(unsigned int line, unsigned int col);
        static void CursorGetPos(unsigned int & line, unsigned int & col);

        // data display methods
        static void PutChar(unsigned int line, unsigned int col,
                            unsigned char attr, char ch);

        static void PutStr(unsigned int line, unsigned int col,
                           unsigned char attr, String & str);

        // data retrieval methods
        static void GetChar(unsigned int line, unsigned int col,
                            unsigned char & attr, char & ch);

        // box display method
        static void DrawBox(unsigned int topLine, unsigned int leftCol,
                            unsigned int btmLine, unsigned int rightCol,
                            unsigned char attr, BoxType typeBox);

        // screen clearing methods
        static void Clear();
        static void ClearLine(unsigned int line, unsigned int col = 0);
    };

// character display method
inline void Screen::PutChar(unsigned int line, unsigned int col,
                            unsigned char attr, char ch)
    {
    unsigned int v = ((unsigned int)attr << 8) | (unsigned char)ch;

    Poke(BaseAdr, (line * Width * 2) + (2 * col), v);
    }

// data retrieval methods
inline void Screen::GetChar(unsigned int line, unsigned int col,
                            unsigned char & attr, char & ch)
    {
    unsigned int v = Peek(BaseAdr, (line * Width * 2) + (2 * col));

    attr = v >> 8;
    ch   = v & 0xFF;
    }

extern Screen Display;

#endif
