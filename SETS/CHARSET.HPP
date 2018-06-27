//  Header:     CharSet
//  Version:    2.00
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides the equivalent of Pascal's SET OF CHAR.
//
//  Written by: Scott Robert Ladd

#if !defined(__CHARSET_HPP)
#define __CHARSET_HPP 1

#include "BitSet.hpp"

class CharSet : public BitSet
    {
    public:
        // constructors
        CharSet() : BitSet(256)
            {}

        CharSet(CharSet & cs) : BitSet(cs)
            {}

        CharSet(char * Values);

        // assignment operator
        void operator = (CharSet & cs)
            {
            BitSet::operator = (cs);
            }
    };

#endif
