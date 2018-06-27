//  Header:     DblList  (Doubly-Linked Lists)
//  Version:    3.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides a general doubly-linked list class
//
//  Written by: Scott Robert Ladd

#include "DblList.hpp"

extern "C"
    {
    #include "stddef.h"
    }

// duplication method
void DoublyLinkedList::Copy(const DoublyLinkedList & dl)
    {
    Head = NULL;
    Tail = NULL;

    DListNode * temp = dl.Head;

    while (temp != NULL)
        {
        if (Tail == NULL)
            {
            Tail = new DListNode;

            if (Tail == NULL)
                ErrorHandler();

            Head = Tail;

            Tail->Next    = NULL;
            Tail->Prev    = NULL;
            Tail->DataPtr = temp->DataPtr;
            }
        else
            {
            Tail->Next = new DListNode;

            if (Tail->Next == NULL)
                ErrorHandler();

            Tail->Next->Next    = NULL;
            Tail->Next->Prev    = Tail;
            Tail->Next->DataPtr = temp->DataPtr;

            Tail = Tail->Next;
            }

        temp = temp->Next;
        }
    }

// constructor
DoublyLinkedList::DoublyLinkedList() : Container()
    {
    Head  = NULL;
    Tail  = NULL;
    }

// copy contructor
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList & dl)
    {
    Copy(dl);
    }

// assignment operator
void DoublyLinkedList::operator = (const DoublyLinkedList & dl)
    {
    this->Empty();

    Count = dl.Count;

    Copy(dl);
    }

// destructor
DoublyLinkedList::~DoublyLinkedList()
    {
    this->Empty();
    }

// remove all items from a list
void DoublyLinkedList::Empty()
    {
    DListNode * temp, * hold;

    temp = Head;

    while (temp != NULL)
        {
        hold = temp->Next;
        delete temp;
        temp = hold;
        }
    }
