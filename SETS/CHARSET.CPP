//  Module:     CharSet
//  Version:    2.00
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides the equivalent of Pascal's SET OF CHAR.
//
//  Written by: Scott Robert Ladd

#include "CharSet.hpp"

CharSet::CharSet(char * Values) : BitSet(256)
    {
    while (*Values != '\x00')
        {
        Include(*Values);
        ++Values;
        }
    }
