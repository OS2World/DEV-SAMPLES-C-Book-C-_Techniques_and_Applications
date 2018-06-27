//  Program:    Creature
//  Version:    2.00
//
//  Language:   C++ 2.0
//  Environ:    MS-DOS, Zortech C++ v2.0x
//
//  Purpose:    SIMECO Creature class definition
//
//  Written by: Scott Robert Ladd

extern "C"
    {
    #include "stdio.h"
    #include "stdlib.h"
    }

#include "Creature.hpp"

// initialize static members
WorkList Creature::CList;

// constructor
Creature::Creature(unsigned char c, int e, int x, int y)
    {
    // set values of members
    Color  = c;
    Energy = e;
    Age    = 0;
    AgeRep = 0;
    PosX   = x;
    PosY   = y;

    // add creature to creature list
    if (CList.Store(this))
        {
        printf("Error: Creature cannot be added to list\n");
        exit(0);
        }
    }
