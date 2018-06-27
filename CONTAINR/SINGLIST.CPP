//  Module:     SingList (Singly-Linked Lists)
//  Version:    3.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides a general set of singly-linked list classes
//
//  Written by: Scott Robert Ladd

#include "SingList.hpp"

extern "C"
    {
    #include "stddef.h"
    }

// duplication method
void SinglyLinkedList::Copy(const SinglyLinkedList & sl)
    {
    Head = NULL;
    Tail = NULL;

    ListNode * temp = sl.Head;

    while (temp != NULL)
        {
        if (Tail == NULL)
            {
            Tail = new ListNode;

            if (Tail == NULL)
                ErrorHandler();

            Head = Tail;

            Tail->Next    = NULL;
            Tail->DataPtr = temp->DataPtr;
            }
        else
            {
            Tail->Next = new ListNode;

            if (Tail->Next == NULL)
                ErrorHandler();

            Tail->Next->Next    = NULL;
            Tail->Next->DataPtr = temp->DataPtr;

            Tail = Tail->Next;
            }

        temp = temp->Next;
        }
    }

// constructor
SinglyLinkedList::SinglyLinkedList() : Container()
    {
    Head  = NULL;
    Tail  = NULL;
    }

// copy contructor
SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList & sl) : Container(sl)
    {
    Copy(sl);
    }

// assignment operator
void SinglyLinkedList::operator = (const SinglyLinkedList & sl)
    {
    this->Empty();

    Count = sl.Count;

    Copy(sl);
    }

// destructor
SinglyLinkedList::~SinglyLinkedList ()
    {
    this->Empty();
    }

// remove all items from a list
void SinglyLinkedList::Empty()
    {
    ListNode * temp, * hold;

    temp = Head;

    while (temp != NULL)
        {
        hold = temp->Next;
        delete temp;
        temp = hold;
        }
    }
