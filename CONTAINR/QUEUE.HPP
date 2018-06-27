//  Header:     Queue    (A queue class)
//  Version:    3.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides a general-purpose queue class
//
//  Written by: Scott Robert Ladd

#if !defined(__QUEUE_HPP)
#define __QUEUE_HPP 1

#include "Stack.hpp"

class Queue : public Stack
    {
    public:
        // constructor
        Queue();

        // copy constructor
        Queue(const Queue & q);

        // assignment constructor
        void operator = (const Queue & q);

        // store an item in a queue
        virtual int Store(void * item);
    };

#endif
