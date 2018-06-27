//  Header:     Grazer
//  Version:    2.00
//
//  Language:   C++ 2.0
//  Environ:    MS-DOS, Zortech C++ v2.0x
//
//  Purpose:    SIMECO Grazer class definition
//
//  Written by: Scott Robert Ladd

#if !defined(__GRAZER_HPP)
#define __GRAZER_HPP 1

#include "Creature.hpp"
#include "BitGrid.hpp"

class Grazer : public Creature
    {
    protected:
        unsigned char Movement[8];  // chance of movement in a given direction
        unsigned char MoveCount;    // sum of values in Movement[]

        unsigned char Sense;        // distance at which food is sensed

        static int Count;           // number of living grazers

        static int MaxEnergy;       // maximum energy
        static int MaxAge;          // maximum age
        static int MaxSense;        // maximum sense value
        static int ReproAge;        // age at which a Grazer can reproduce
        static int RepEnergy;       // energy required for reproduction
        static int FoodValue;       // energy obtained from eating food

        static int NoMoveGenes;     // number of movement genes

        static int MoveTable[8][2]; // class-global table of movements

        static BitGrid *FoodSupply; // pointer to supply of food for grazers

        static int MaxX;            // maximum X dimension for Grazer
        static int MaxY;            // maximum Y dimension for Grazer

    public:
        // basic constructor
        Grazer(int x, int y);

        // copy constructor (used in birth of a new Grazer)
        Grazer(const Grazer & G);

        // destructor
        ~Grazer();

        // retrieve number of living grazers
        static int Population()
            {
            return Count;
            }

        // set food supply and area dimensions
        static void SetRegion(BitGrid * food, int xmax, int ymax);

        // ask grazer to do something
        virtual int Move();

        // tell grazer to draw itself
        virtual void Draw();

        // tell grazer to erase itself
        virtual void Erase();
    };



#endif
