//  Header:     WorkList (A Useful Kind of Doubly-Linked List)
//  Version:    3.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    I'm not sure what to call this kind of doubly-linked list;
//              it's been so useful, I needed to create a class for it. So,
//              WorkList is what it's called!
//
//  Written by: Scott Robert Ladd

#if !defined(__WORKLIST_HPP)
#define __WORKLIST_HPP 1

#include "DblList.hpp"

class WorkList : public DoublyLinkedList
    {
    protected:
        DListNode * Current; // currently selected node in the list

    public:
        // constructor
        WorkList();

        // copy constructor
        WorkList(const WorkList & wl);

        // assignment operator
        void operator = (const WorkList & wl);

        // store an item
        virtual int Store(void * item);

        // examine an item
        virtual void * Examine();

        // read and remove an item
        virtual void * Retrieve();

        // delete an item from the list
        virtual int Delete(void * item);

        // go to head of list
        virtual void GoToHead();

        // go to end of list
        virtual void GoToTail();

        // go to next item in list
        virtual void GoNext();

        // go to previous item in list
        virtual void GoPrev();
    };

#endif
