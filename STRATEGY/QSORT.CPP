//  Module:     QSort
//  Version:    1.00
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    A QuickSort for arrays
//
//  Written by: Scott Robert Ladd

#include "QSort.hpp"

extern "C"
    {
    #include "string.h"
    }

void QuickSortArray::Sort(void * arrayPtr, int arrayLen, int itemSize,
                          int (* CompareFunc)(void * item1, void * item2))
    {
    SortArray::Sort(arrayPtr, arrayLen, itemSize, CompareFunc);

    temp = new char [Size];

    QSRecursive(1,arrayLen);

    delete temp;
    }

void QuickSortArray::QSRecursive(int l, int r)
    {
    int i, j;
    void * x, * y;

    i = l;
    j = r;
    x = ItemPtr((l + r) / 2);

    do  {
        while (Compare(ItemPtr(i), x))
            ++i;

        while (Compare(x, ItemPtr(j)))
            --j;

        if (i <= j)
            {
            x = ItemPtr(i);
            y = ItemPtr(j);

            memcpy(temp,x,Size);
            memcpy(x,y,Size);
            memcpy(y,temp,Size);

            ++i;
            --j;
            }

        if (l < j)
            QSRecursive(l,j);

        if (i < r)
            QSRecursive(i,r);
        }
    while (i <= j);
    }
