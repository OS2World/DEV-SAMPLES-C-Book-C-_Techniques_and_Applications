//  Header:     Queue    (A queue class)
//  Version:    3.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides a general-purpose queue class
//
//  Written by: Scott Robert Ladd

#include "Queue.hpp"

extern "C"
    {
    #include "stddef.h"
    }

// constructor
Queue::Queue() : Stack()
    {}

// copy constructor
Queue::Queue(const Queue & q) : Stack(q)
    {}

// assignment constructor
void Queue::operator = (const Queue & q)
    {
    this->Stack::operator = (q);
    }

// add new item
int Queue::Store(void * item)
    {
    ListNode * new_node;

    new_node = new ListNode;

    if (NULL == new_node)
        return 1;

    new_node->Next    = NULL;
    new_node->DataPtr = item;

    if (Count > 0)
        {
        Tail->Next = new_node;
        Tail       = new_node;
        }
    else
        {
        Head = new_node;
        Tail = new_node;
        }

    ++Count;

    return 0;
    }
