//  Header:     SingList (Singly-Linked Lists)
//  Version:    3.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides a general set of singly-linked list classes
//
//  Written by: Scott Robert Ladd

#if !defined(__SINGLIST_HPP)
#define __SINGLIST_HPP 1

#include "Containr.hpp"

class SinglyLinkedList : public Container
    {
    protected:
        // structure of a node in a list
        struct ListNode
            {
            ListNode  *  Next;
            void      *  DataPtr;
            };

        ListNode * Head;  // pointer to first node
        ListNode * Tail;  // pointer to the last node

        // duplication method
        void Copy(const SinglyLinkedList & sl);

    public:
        // constructor
        SinglyLinkedList();

        // copy contructor
        SinglyLinkedList(const SinglyLinkedList & sl);

        // assignment operator
        void operator = (const SinglyLinkedList & sl);

        // destructor
        ~SinglyLinkedList();

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
