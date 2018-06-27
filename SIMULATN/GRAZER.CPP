//  Header:     Grazer
//  Version:    2.00
//
//  Language:   C++ 2.0
//  Environ:    MS-DOS, Zortech C++ v2.0x
//
//  Purpose:    SIMECO Grazer class definition
//
//  Written by: Scott Robert Ladd

// include class definition
#include "Grazer.hpp"

// include C library headers
extern "C"
    {
    #include "stdio.h"
    #include "stdlib.h"
    #include "graphvga.h"
    }

// this macro returns a random number between 1 and n
#define RandVal(n) ((rand() % n) + 1)

// initialize the static members of Grazer class
int Grazer::Count       =    0;
int Grazer::MaxEnergy   = 3000;
int Grazer::MaxAge      =  300;
int Grazer::MaxSense    =    3;
int Grazer::ReproAge    =  100;
int Grazer::RepEnergy   = 2000;
int Grazer::FoodValue   =  150;
int Grazer::NoMoveGenes =    8;

int Grazer::MoveTable[8][2] =
    { {-3, -3}, { 0, -3}, { 3, -3},
      {-3,  0},           { 3,  0},
      {-3,  3}, { 0,  3}, { 3,  3} };

// globals defining area which grazers live in
BitGrid * Grazer::FoodSupply = NULL;

int Grazer::MaxX = 0;
int Grazer::MaxY = 0;

// basic constructor for a new creature
Grazer::Grazer(int x, int y)
    : Creature(15,1500,x,y)
    {
    for (int i = 0; i < NoMoveGenes; ++ i)
        Movement[i] = 1;

    MoveCount = NoMoveGenes;

    Sense = 0;

    ++Count;

    Draw();
    }

// copy constructor
Grazer::Grazer(const Grazer & G)
    : Creature(15,G.Energy,G.PosX,G.PosY)
    {
    for (int i = 0; i < NoMoveGenes; ++i)
        Movement[i] = G.Movement[i];

    MoveCount = G.MoveCount;

    Sense = G.Sense;

    int choice = RandVal(10);

    switch (choice)
        {
        case 1: // modify movement genes
        case 2:
        case 3:
            int move = RandVal(NoMoveGenes) - 1;

            if (1 == RandVal(2))
                {
                if (Movement[move] == 1)
                    {
                    ++Movement[move];
                    ++MoveCount;
                    }
                }
            else
                {
                if (Movement[move] == 2)
                    {
                    --Movement[move];
                    --MoveCount;
                    }
                }
            break;

        case 4: // modify sense value
            if (1 == RandVal(2))
                {
                if (Sense < MaxSense)
                    ++Sense;
                }
            else
                {
                if (Sense > 0)
                    --Sense;
                }
        }

    ++Count;

    Draw();
    }

// destructor
Grazer::~Grazer()
    {
    if (CList.Delete(this))
        {
        printf("Error: Creature cannot be deleted from list\n");
        exit(0);
        }

    Erase();

    --Count;
    }

// set food supply and area dimensions
void Grazer::SetRegion(BitGrid * food, int xmax, int ymax)
    {
    FoodSupply = food;

    MaxX = xmax;
    MaxY = ymax;
    }

// ask grazer to do something
int Grazer::Move()
    {
    ++Age;
    ++AgeRep;

    if ((AgeRep >= ReproAge) && (Energy >= RepEnergy))
        {
        AgeRep = 0;

        Energy /= 2;

        Grazer * newG = new Grazer(*this);

        if (newG == NULL)
            {
            printf("Error! Grazer Repro\n");
            exit(1);
            }
        }

    int i, x, y, newx, newy, m, weight, move;

    if (Sense > 0)
        {
        int move_value, j, ix, iy;

        int hi_value = -1;

        move = 0;

        for (i = 0; i < NoMoveGenes; ++i)
            {
            move_value = 0;

            x = PosX;
            y = PosY;

            for (j = 0; j < Sense; ++j)
                {
                x += MoveTable[i][0];
                y += MoveTable[i][1];

                if (x < 1) x = MaxX;
                if (x > MaxX) x = 1;
                if (y < 1) y = MaxY;
                if (y > MaxY) y = 1;

                for (ix = x - 1; ix <= x + 1; ++ix)
                    for (iy = y - 1; iy <= y + 1; ++iy)
                        if (FoodSupply->IsSet(ix,iy))
                            ++move_value;
                }

            if (move_value > hi_value)
                {
                hi_value = move_value;
                move = i;
                }
            else
                if ((move_value == hi_value) && (Movement[i] >= Movement[move]))
                    if ((Movement[i] > Movement[move]) || (RandVal(2) == 1))
                        move = i;
            }
        }
    else
        {
        weight = Movement[0];
        m      = RandVal(MoveCount);

        move =  0;

        while (m > weight)
            {
            ++move;
            weight += Movement[move];
            }
        }

    if ((move == 0) || (move == 2) || (move == 5) || (move == 7))
        Energy -= 5;
    else
        Energy -= 3;

    // did it die?
    if ((Age == MaxAge) || (Energy <= 0))
        return 1;

    newx = PosX + MoveTable[move][0];
    newy = PosY + MoveTable[move][1];

    Erase();

    PosX = newx;
    PosY = newy;

    if (PosX < 1) PosX = MaxX;
    if (PosX > MaxX) PosX = 1;
    if (PosY < 1) PosY = MaxY;
    if (PosY > MaxY) PosY = 1;

    for (x = PosX - 1; x <= PosX + 1; ++x)
        for (y = PosY - 1; y <= PosY + 1; ++y)
            if (FoodSupply->IsSet(x,y))
                {
                Energy += FoodValue;
                FoodSupply->Exclude(x,y);
                }

    Draw();

    return 0;
    }

// tell grazer to draw itself
void Grazer::Draw()
    {
    for (int x = PosX - 1; x <= PosX + 1; ++x)
        for (int y = PosY - 1; y <= PosY + 1; ++y)
            PlotPixel(x,y,Color);
    }

// tell grazer to erase itself
void Grazer::Erase()
    {
    for (int x = PosX - 1; x <= PosX + 1; ++x)
        for (int y = PosY - 1; y <= PosY + 1; ++y)
            PlotPixel(x,y,0);
    }
