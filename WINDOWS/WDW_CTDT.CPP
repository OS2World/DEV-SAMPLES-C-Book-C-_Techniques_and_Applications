//  Module:     Wdw_ctdt  (Window Class)
//  Version:    2.11
//
//  Language:   C++ 2.0
//  Environ:    IBM-PC MS-DOS
//
//  Purpose:    Constructor / destructor
//
//  Written by: Scott Robert Ladd

#include "Str.hpp"
#include "Window.hpp"

extern "C"
    {
    #include "string.h"
    #include "stddef.h"
    }

// constructor
Window::Window(unsigned int line, unsigned int col,
               unsigned int len,  unsigned int wid,
               unsigned char iattr, unsigned char battr,
               BoxType bord, String & heading, int wrapMode)
    : Header(heading)
    {
    if (!Initialized)
        FirstTime();

    // make sure window is created on the scree
    if ((line > MaxLength) || (col > MaxWidth))
        {
        line = 0;
        col  = 0;
        }

    // set instance variables
    HomeLine = line;
    HomeCol  = col;
    Length   = len;
    Width    = wid;
    CrsLine  = 0;
    CrsCol   = 0;

    InsideColor = iattr;
    BorderColor = battr;

    Border = bord;

    Wrapped   = wrapMode;
    Concealed = 0;

    // no border, no heading
    if (Border == BT_NONE)
        Header = "";

    // add the window to the list
    WdwList.Store(this);

    // allocate buffer to store window contents
    BufferSW = new WindowWord [Length * Width];

    if (BufferSW == NULL)
        ErrorHandler();

    // make the new window the top window
    TopWindow = this;

    PlotOwnership();

    // clear the window
    ClearAll();

    // and display it
    Paint();
    }

// destructor
Window::~Window()
    {
    // remove window from list
    WdwList.Delete(this);

    // get a new top window
    WdwList.GoToHead();

    TopWindow = (Window *)WdwList.Examine();

    // free buffer space
    delete BufferSW;

    // restack all windows
    Restack();
    return;
    }
