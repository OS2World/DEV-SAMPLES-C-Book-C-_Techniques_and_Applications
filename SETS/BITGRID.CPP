//  Header:     BitGrid
//  Version:    2.00
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    A class for a two-dimensional array of bits. Only those methods
//              defined in this file should be used on a BitGrid.
//
//  Written by: Scott Robert Ladd

#if !defined(__BITGRID_HPP)
#define __BITGRID_HPP 1

#include "BitSet.hpp"

class BitGrid : public BitSet
    {
    private:
        unsigned long Width;

    public:
        // constructor
        BitGrid(unsigned long x_dim, unsigned long y_dim)
            : BitSet(x_dim * y_dim)
            {
            Width = x_dim;
            }

        // include a bit
        void Include(unsigned long x_pos, unsigned long y_pos)
            {
            BitSet::Include(y_pos * Width + x_pos);
            }

        // exclude a bit
        void Exclude(unsigned long x_pos, unsigned long y_pos)
            {
            BitSet::Exclude(y_pos * Width + x_pos);
            }

        //
        int IsSet(unsigned long x_pos, unsigned long y_pos)
            {
            return BitSet::operator [] (y_pos * Width + x_pos);
            }
    };

#endif
