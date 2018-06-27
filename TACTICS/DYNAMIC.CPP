//  Module:     Dynamic     (Improved Dynamic Memory Allocation)
//  Version:    1.00
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Implements an improved memory allocation scheme for C++ by
//              overloading the built-in new and delete operators.
//
//  Written by: Scott Robert Ladd

#include "Dynamic.hpp"

extern "C"
    {
    #include "stdlib.h"
    }

void * operator new (unsigned int size)
    {
    void * temp = malloc(size);

    return temp;
    }

void operator delete (void * ptr)
    {
    free(ptr);
    }

void * _vec_new(
    void *       aptr,
    unsigned int num,
    size_t       size,
    void *       (* ctor)(void *))
    {
    aptr = malloc(num * size);

    if ((ctor != NULL) && (aptr != NULL))
        {
        for (unsigned int n = 0; n < num; ++n)
            ctor((char *)aptr + n * size);
        }

    return aptr;
    }

void _vec_delete(
    void *       aptr,
    unsigned int num,
    size_t       size,
    int          (*dtor)(int, void *),
    int          freeup)
    {
    if (aptr == NULL)
        return;

    if (dtor != NULL)
        {
        for (unsigned int n = 0; n < num; ++n)
            dtor(2,(char *)aptr + n * size);
        }

    if (freeup)
        free(aptr);
    }
