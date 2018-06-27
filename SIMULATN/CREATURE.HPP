//  Header:     Creature
//  Version:    2.00
//
//  Language:   C++ 2.0
//  Environ:    MS-DOS, Zortech C++ v2.0x
//
//  Purpose:    SIMECO Creature class definition
//
//  Written by: Scott Robert Ladd

#if !defined(__CREATURE_HPP)
#define __CREATURE_HPP 1

#include "WorkList.hpp"

class Creature
    {
    protected:
        unsigned char Color;     // this Creature's color

        int Energy;              // current energy level
        int Age;                 // current age
        int AgeRep;              // age since last reproduction

        int PosX, PosY;          // horizontal position on screen

    public:
        // public list of all creatures
        static WorkList CList;   // list of all creatures in existence

        // constructor
        Creature(unsigned char c, int e, int x, int y);

        // ask creature to perform an action
        virtual int Move() = 0;

        // tell creature to draw itself
        virtual void Draw() = 0;

        // tell creature to erase itself
        virtual void Erase() = 0;
    };

#endif
