//  Program:    SimEco   (Simulated Ecosystem)
//  Version:    2.00
//
//  Language:   C++ 2.0
//  Environ:    MS-DOS, Zortech C++ v2.0x
//
//  Purpose:    This program simulates a primitive ecosystem.
//
//  Written by: Scott Robert Ladd

// include standard C libraries
extern "C"
    {
    #include "conio.h"
    #include "time.h"
    #include "stdio.h"
    #include "stdlib.h"
    #include "graphvga.h"
    }

// this macro returns a random number between 1 and n
#define RandVal(n) ((rand() % n) + 1)

// include C++ classes
#include "Creature.hpp"
#include "Grazer.hpp"
#include "BitGrid.hpp"

// These definitions change how food is distributed
// #define GARDEN 1
#define NORMAL_FOOD 1
#define NEW_FOOD 2

// constants which define the size of the grid array
const int MaxX = 630;
const int MaxY = 450;

// global data items
BitGrid * GrazerFood;

// function prototypes
int  Initialize();
void LifeCycle();
void cdecl Finish();
int  main();

int Initialize()
    {
    GraphInit();

    // set function to be called at exit
    if (atexit(Finish))
        return 1;

    srand(unsigned(time(NULL)));

    GrazerFood = new BitGrid (630, 450);

    Grazer::SetRegion(GrazerFood, MaxX, MaxY);

    Grazer * G;
    int i, x, y;

    for (i = 0; i < 40; ++i)
        {
        x = RandVal(MaxX);
        y = RandVal(MaxY);

        G = new Grazer(x,y);

        if (G == NULL)
            {
            printf("Error: Init Grazers\n");
            return 2;
            }
        }

    for (i = 0; i < 4000; ++i)
        {
        do  {
            x = RandVal(MaxX);
            y = RandVal(MaxY);
            }
        while (GrazerFood->IsSet(x,y));

        GrazerFood->Include(x,y);

        PlotPixel(x,y,14);
        }

    return 0;
    }

void LifeCycle()
    {
    Creature * C;
    unsigned long move;
    char stat_line[20];
    int x, y, i;

    move = 0L;

    while ((Grazer::Population() > 0) && !kbhit())
        {
        Creature::CList.GoToHead();

        while (1)
            {
            C = Creature::CList.Examine();

            if (NULL == C)
                break;

            Creature::CList.GoNext();

            if (C->Move())
                delete (Grazer *)C;
            }

        for (i = 0; i < NEW_FOOD; ++i)
            {
            #if defined(GARDEN)
                do  {
                    x = RandVal(100) + 270;
                    y = RandVal(100) + 175;
                    }
                while (GrazerFood->IsSet(x,y));

                GrazerFood->Include(x,y);

                PlotPixel(x,y,14);
            #endif

            #if defined(NORMAL_FOOD)
                do  {
                    x = RandVal(MaxX);
                    y = RandVal(MaxY);
                    }
                while (GrazerFood->IsSet(x,y));

                GrazerFood->Include(x,y);

                PlotPixel(x,y,14);
            #endif
            }

        ++move;

        sprintf(stat_line,"M: %6ld, C: %3d",move,Grazer::Population());

        PutGraphString(465,10,stat_line,15,0);
        }
    }

void cdecl Finish()
    {
    while (!kbhit()) ;

    if (!getch()) getch();

    GraphDone();
    }

int main()
    {
    if (Initialize())
        return 1;

    LifeCycle();

    return 0;
    }
