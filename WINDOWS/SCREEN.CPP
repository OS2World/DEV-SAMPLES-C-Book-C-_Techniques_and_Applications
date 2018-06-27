//  Module:     Screen  (MS-DOS Text Video Display Class)
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

#include "Screen.hpp"
#include "Str.hpp"

extern "C"
    {
    #include "dos.h"
    }

// assign values to static class members
unsigned int  Screen::Width        = 0;
unsigned int  Screen::Length       = 0;
unsigned int  Screen::BaseAdr      = 0;
unsigned int  Screen::CursorShape  = 0;
int           Screen::CursorHidden = 0;

Screen Display;

// constructor
Screen::Screen()
    {
    ++HowMany;

    if (HowMany > 1)
        return;

    union REGS regs;

    regs.h.ah = 0x0f;

    int86(0x10,&regs,&regs);

    if (regs.h.al == 0x07)
        BaseAdr = 0xB000;
    else
        BaseAdr = 0xB800;

    Width = (int) regs.h.ah;

    regs.x.ax = 0x1130;
    regs.h.bh = 0;
    regs.x.dx = 0;

    int86(0x10,&regs,&regs);

    Length = regs.x.dx + 1;

    if (Length == 1)
        Length = 25;

    Clear();

    CursorHidden = 0;
    }

// destructor
Screen::~Screen()
    {
    --HowMany;

    if (HowMany > 0)
        return;

    Clear();

    CursorSetPos(0,0);
    }

// access methods
void Screen::Dimensions(unsigned int & wid, unsigned int & len)
    {
    wid = Width;
    len = Length;
    }

// cursor methods
void Screen::CursorHide()
    {
    if (CursorHidden)
        return;

    union REGS regs;

    regs.h.ah = 3;
    regs.h.bh = 0;

    int86(0x10,&regs,&regs);

    CursorShape = regs.x.cx;

    regs.h.ah = 1;
    regs.x.cx = 0x2000;

    int86(0x10,&regs,&regs);

    CursorHidden = 1;
    }

void Screen::CursorUnhide()
    {
    if (!CursorHidden)
        return;

    union REGS regs;

    regs.h.ah = 1;
    regs.x.cx = CursorShape;

    int86(0x10,&regs,&regs);

    CursorHidden = 0;
    }

void Screen::CursorSetPos(unsigned int line, unsigned int col)
    {
    union REGS regs;

    regs.h.ah = 2;
    regs.h.bh = 0;
    regs.h.dh = line;
    regs.h.dl = col;

    int86(0x10,&regs,&regs);
    }

void Screen::CursorGetPos(unsigned int & line, unsigned int & col)
    {
    union REGS regs;

    regs.h.ah = 3;
    regs.h.bh = 0;

    int86(0x10,&regs,&regs);

    line = regs.h.dh;
    col  = regs.h.dl;
    }

// display a text string method
void Screen::PutStr(unsigned int line, unsigned int col,
                    unsigned char attr, String & str)
    {
    for (unsigned int i = 0; str[i] != '\000'; ++i)
        PutChar(line, col + i, attr, str[i]);
    }



// box display methods
void Screen::DrawBox(unsigned int topLine, unsigned int leftCol,
                     unsigned int btmLine, unsigned int rightCol,
                     unsigned char attr, BoxType typeBox)
    {
    if ((typeBox == BT_NONE) || (leftCol >= rightCol) || (topLine >= btmLine))
        return;

    char v, h;

    switch (typeBox)
        {
        case BT_SINGLE:
            v = '\xB3';
            h = '\xC4';
            PutChar(topLine, leftCol,  attr, '\xDA');
            PutChar(topLine, rightCol, attr, '\xBF');
            PutChar(btmLine, leftCol,  attr, '\xC0');
            PutChar(btmLine, rightCol, attr, '\xD9');
            break;
        case BT_DOUBLE:
            v = '\xBA';
            h = '\xCD';
            PutChar(topLine, leftCol,  attr, '\xC9');
            PutChar(topLine, rightCol, attr, '\xBB');
            PutChar(btmLine, leftCol,  attr, '\xC8');
            PutChar(btmLine, rightCol, attr, '\xBC');
            break;
        case BT_SOLID:
            v = '\xDB';
            h = '\xDB';
            PutChar(topLine, leftCol,  attr, '\xDB');
            PutChar(topLine, rightCol, attr, '\xDB');
            PutChar(btmLine, leftCol,  attr, '\xDB');
            PutChar(btmLine, rightCol, attr, '\xDB');
        }

    for (int c = leftCol + 1; c < rightCol; ++c)
        {
        PutChar(topLine, c, attr, h);
        PutChar(btmLine, c, attr, h);
        }

    for (int l = topLine + 1; l < btmLine; ++l)
        {
        PutChar(l, leftCol,  attr, v);
        PutChar(l, rightCol, attr, v);
        }
    }


// screen clearing methods
void Screen::Clear()
    {
    for (int l = 0; l < Length; ++l)
        {
        for (int c = 0; c < Width; ++c)
            PutChar(l,c,7,' ');
        }
    }

void Screen::ClearLine(unsigned int line, unsigned int col)
    {
    for (int c = col; c < Width; ++c)
        PutChar(line,c,7,' ');
    }
