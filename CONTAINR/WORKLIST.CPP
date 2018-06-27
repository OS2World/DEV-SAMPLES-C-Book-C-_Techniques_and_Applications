//  Module:     WorkList (A Useful Kind of Doubly-Linked List)
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

#include "WorkList.hpp"

extern "C"
    {
    #include "stddef.h"
    }

// constructor
WorkList::WorkList() : DoublyLinkedList()
    {
    Current = NULL;
    }

// copy constructor
WorkList::WorkList(const WorkList & wl) : DoublyLinkedList(wl)
    {}

// assignment operator
void WorkList::operator = (const WorkList & wl)
    {
    DoublyLinkedList::operator = (wl);

    Current = Head;
    }

// store an item
int WorkList::Store(void * item)
    {
    DListNode * new_item;

    new_item = new DListNode;

    if (item == NULL)
        return 1;

    new_item->Prev    = NULL;
    new_item->Next    = NULL;
    new_item->DataPtr = item;

    if (Head == NULL)
        {
        Head    = new_item;
        Tail    = new_item;
        Current = new_item;
        }
    else
        {
        Head->Prev = new_item;
        new_item->Next = Head;
        Head = new_item;
        }

    ++Count;

    return 0;
    }

// examine an item
void * WorkList::Examine()
    {
    if (Current == NULL)
        return NULL;
    else
        return Current->DataPtr;
    }

// read and remove an item
void * WorkList::Retrieve()
    {
    void * value = Examine();

    Delete(value);

    return value;
    }

// delete an item from the list
int WorkList::Delete(void * item)
    {
    DListNode * temp;

    temp = Head;

    while (temp != NULL)
        {
        if (temp->DataPtr == item)
            {
            if (temp == Current)
                Current = temp->Next;

            if (temp->Prev == NULL)
                {
                Head = temp->Next;

                if (Head != NULL)
                    Head->Prev = NULL;

                if (temp->Next == NULL)
                    Tail = NULL;
                }
            else
                {
                temp->Prev->Next = temp->Next;

                if (temp->Next == NULL)
                    Tail = temp->Prev;
                else
                    temp->Next->Prev = temp->Prev;
                }

            delete temp;

            --Count;

            return 0;
            }

        temp = temp->Next;
        }

    return 1;
    }

// go to head of list
void WorkList::GoToHead()
    {
    Current = Head;
    }

// go to end of list
void WorkList::GoToTail()
    {
    Current = Tail;
    }

// go to next item in list
void WorkList::GoNext()
    {
    if (Current != NULL)
        Current = Current->Next;
    }

// go to next item in list
void WorkList::GoPrev()
    {
    if (Current != NULL)
        Current = Current->Prev;
    }
