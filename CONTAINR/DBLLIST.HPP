//  Header:     DblList  (Doubly-Linked Lists)
//  Version:    3.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides a general doubly-linked list class
//
//  Written by: Scott Robert Ladd

#if !defined(__DBLLIST_HPP)
#define __DBLLIST_HPP 1

#include "Containr.hpp"

class DoublyLinkedList : public Container
    {
    protected:
        // structure of a node in a list
        struct DListNode
            {
            DListNode * Prev;
            DListNode * Next;
            void      * DataPtr;
            };

        // pointers to first and last nodes in list
        DListNode * Head;
        DListNode * Tail;

        // duplication method
        void Copy(const DoublyLinkedList & sl);

    public:
        // constructor
        DoublyLinkedList();

        // copy contructor
        DoublyLinkedList(const DoublyLinkedList & sl);

        // assignment operator
        void operator = (const DoublyLinkedList & sl);

        // destructor
        ~DoublyLinkedList();

        // store an item
        virtual int Store(void * item) = 0;

        // examine an item
        virtual void * Examine() = 0;

        // retrieve an item
        virtual void * Retrieve() = 0;

        // remove all items from a list
        virtual void Empty();
    };

#endif
