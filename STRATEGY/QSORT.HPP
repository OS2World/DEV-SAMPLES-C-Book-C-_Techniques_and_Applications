//  Header:     QSort
//  Version:    1.00
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    A QuickSort for arrays
//
//  Written by: Scott Robert Ladd

#if !defined(__QSORT_HPP)
#define __QSORT_HPP 1

#include "Sort.hpp"

class QuickSortArray : public SortArray
    {
    private:
        void * temp;

        void QSRecursive(int l, int r);

    public:
        virtual void Sort(void * arrayPtr, int arrayLen, int itemSize,
                          int (* CompareFunc)(void * item1, void * item2));
    };

#endif
