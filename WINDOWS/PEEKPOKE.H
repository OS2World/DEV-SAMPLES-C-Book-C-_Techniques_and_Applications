/*
    Header:     PeekPoke
    Version:    1.01

    Language:   Intel 80x86 Macro Assembler
    Environ:    IBM-PC compatible

    Purpose:    Provides functions to peek and poke values into specific
                memory locations.

    Written by: Scott Robert Ladd
*/

/* prototypes */

void Poke(unsigned int segm, unsigned int offs, unsigned int value);

unsigned int Peek(unsigned int segm, unsigned int offs);
