//  Header:     Window  (Window Class)
//  Version:    2.11
//
//  Language:   C++ 2.0
//  Environ:    IBM-PC MS-DOS
//
//  Purpose:    Provides the definition of the stacked Windows module
//
//  Written by: Scott Robert Ladd

#if !defined(__WINDOW_HPP)
#define __WINDOW_HPP 1

#include "Screen.hpp"
#include "Str.hpp"
#include "WorkList.hpp"

extern "C"
    {
    #include "stddef.h"
    }

class Window
    {
    protected:
        static WorkList  WdwList;
        static Window ** ScrnOwner;
        static int       Initialized;
        static Window *  TopWindow;

        static unsigned int MaxLength;
        static unsigned int MaxWidth;

        unsigned int HomeLine;
        unsigned int HomeCol;
        unsigned int Length;
        unsigned int Width;
        unsigned int CrsLine;
        unsigned int CrsCol;

        unsigned char InsideColor;
        unsigned char BorderColor;

        BoxType Border;

        // header text
        String Header;

        // flags
        int Wrapped;
        int Concealed;

        // buffer for this window
        struct WindowWord
            {
            unsigned char Attribute;
            char Symbol;
            };

        WindowWord * BufferSW;

        // private methods
        static void FirstTime();

        void Display(int line, int col,
                     unsigned char attr, char ch);

        static void Restack();

        void PlotOwnership();

        static void (* ErrorHandler)();

    public:
        // constructor
        Window(unsigned int  line, unsigned int  col,
               unsigned int  len,  unsigned int  wid,
               unsigned char iattr, unsigned char battr,
               BoxType bord,
               String & heading, int wrapMode = 0);

        // copy constructor
        Window(const Window & w);

        // assignment operator
        void operator = (const Window & w);

        // destructor
        ~Window();

        // assign an exception handler
        static void SetErrorHandler(void (* userHandler)());

        // paint a window
        void Paint();

        // paint a line
        void PaintLine(unsigned int line);

        // change position
        void Move(unsigned int line, unsigned int col);

        // make this the top window
        void Hoist();

        // conceal this window
        void Conceal();

        // reveal this window
        void Reveal();

        // turn wrap on
        void WrapOn();

        // turn wrap off
        void WrapOff();

        // change headings
        void SetHead(String & heading);

        // set the cursor position
        void SetCursor(unsigned int line, unsigned int col);

        // get the cursor position
        void GetCursor(unsigned int & line, unsigned int & col);

        // store a character
        void PutChar(unsigned int  line, unsigned int col,
                     unsigned char attr, char c);

        // store a string
        void PutStr(unsigned int line, unsigned int col,
                    unsigned char attr, String & s);

        // clear entire window
        void ClearAll();

        // clear one line of window
        void ClearLine(unsigned int line, unsigned int col = 0);
    };

#endif
