//  Module:     HSort
//  Version:    1.00
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    A HeapSort for arrays
//
//  Written by: Scott Robert Ladd

#include "HSort.hpp"

extern "C"
    {
    #include "string.h"
    }


void HeapSortArray::Sift()
    {
    int i, j;

    i = l;
    j = 2 * l;

    src = ItemPtr(i);
    memcpy(temp,src,Size);

    while (j <= r)
        {
        if (j < r)
            if (Compare(ItemPtr(j),ItemPtr(j + 1)))
                ++j;

        if (Compare(ItemPtr(j),temp))
            goto done;

        src  = ItemPtr(j);
        dest = ItemPtr(i);

        memcpy(dest,src,Size);

        i = j;
        j = 2 * i;
        }

    done:

    dest = ItemPtr(i);

    memcpy(dest,temp,Size);
    }

void HeapSortArray::Sort(void * arrayPtr, int arrayLen, int itemSize,
                         int (* CompareFunc)(void * item1, void * item2))
    {
    SortArray::Sort(arrayPtr, arrayLen, itemSize, CompareFunc);

    temp = new char [Size];

    l = (arrayLen / 2) + 1;
    r = arrayLen;

    while (l > 1)
        {
        --l;
        Sift();
        }

    while (r > 1)
        {
        src  = ItemPtr(1);
        dest = ItemPtr(r);

        memcpy(temp,src,Size);
        memcpy(src,dest,Size);
        memcpy(dest,temp,Size);

        --r;
        Sift();
        }

    delete temp;
    }
