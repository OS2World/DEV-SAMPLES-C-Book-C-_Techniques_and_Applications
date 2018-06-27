//  Module:     Stack    (A stack class)
//  Version:    3.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides a a stack class for C++
//
//  Written by: Scott Robert Ladd

#include "Stack.hpp"

extern "C"
    {
    #include "stddef.h"
    }

// constructor
Stack::Stack() : SinglyLinkedList()
    {}

// copy constructor
Stack::Stack(const Stack & st) : SinglyLinkedList(st)
    {}

// assignment operator
void Stack::operator = (const Stack & st)
    {
    this->SinglyLinkedList::operator = (st);
    }

// add new item
int Stack::Store(void * item)
    {
    ListNode * new_node;

    new_node = new ListNode;

    if (NULL == new_node)
        return 1;

    new_node->Next    = Head;
    new_node->DataPtr = item;

    Head = new_node;

    if (Tail == NULL)
        Tail = new_node;

    ++Count;

    return 0;
    }

// examine the top item on the stack
void * Stack::Examine()
    {
    if (Count == 0)
        return NULL;

    return Head->DataPtr;
    }

// read and remove the top item on the stack
void * Stack::Retrieve()
    {
    ListNode * temp;
    void *     value;

    if (Count == 0)
        return NULL;

    value = Head->DataPtr;
    temp  = Head->Next;

    delete Head;

    Head = temp;

    --Count;

    return value;
    }
