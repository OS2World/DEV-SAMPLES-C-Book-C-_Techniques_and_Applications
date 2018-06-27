//  Header:     HSort
//  Version:    1.00
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    A HeapSort for arrays
//
//  Written by: Scott Robert Ladd

#if !defined(__HSORT_HPP)
#define __HSORT_HPP 1

#include "Sort.hpp"

class HeapSortArray : public SortArray
    {
    private:
        int  l, r;
        void * temp, * src, * dest;

        void Sift();

    public:
        virtual void Sort(void * arrayPtr, int arrayLen, int itemSize,
                          int (* CompareFunc)(void * item1, void * item2));
    };

#endif
