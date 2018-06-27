//  Header:     Stack    (A stack class)
//  Version:    3.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides a a stack class for C++
//
//  Written by: Scott Robert Ladd

#if !defined(__STACK_HPP)
#define __STACK_HPP 1

#include "SingList.hpp"

class Stack : public SinglyLinkedList
    {
    public:
        // constructor
        Stack();

        // copy constructor
        Stack(const Stack & st);

        // assignment operator
        void operator = (const Stack & st);

        // store an item in a stack
        virtual int Store(void * item);

        // examine the top item in the stack
        virtual void * Examine();

        // retrieve the top item in a stack (and remove it)
        virtual void * Retrieve();
    };

#endif
