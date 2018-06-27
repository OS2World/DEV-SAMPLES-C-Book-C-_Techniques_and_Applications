//  Header:     Dynamic     (Improved Dynamic Memory Allocation)
//  Version:    1.01
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Implements a template for replacing C++'s default memory
//              allocation operators
//
//  Written by: Scott Robert Ladd

extern "C"
    {
    #include "stddef.h"
    }

void * operator new (size_t size);

void operator delete (void * ptr);

extern "C" {
    void * _vec_new (
        void *       aptr,
        unsigned int num,
        size_t       size,
        void *       (*ctor)(void *));

    void _vec_delete (
        void *       aptr,
        unsigned int num,
        size_t       size,
        int          (*dtor)(int, void *),
        int          freeup);
    }
