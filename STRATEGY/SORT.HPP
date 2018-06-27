//  Header:     Sort
//  Version:    1.00
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    A generic array sorting class
//
//  Written by: Scott Robert Ladd

#if !defined(__SORT_HPP)
#define __SORT_HPP 1

class SortArray
    {
    protected:
        void * Array;
        int    Size;

        int (* Compare)(void *, void *);

        void * ItemPtr(int item)
            {
            return (void *)((char *)Array + (Size * (item - 1)));
            }

    public:
        virtual void Sort(void * arrayPtr, int arrayLen, int itemSize,
                          int (* CompareFunc)(void * item1, void * item2))
            {
            Array = arrayPtr;
            Size  = itemSize;

            Compare = CompareFunc;
            }
    };

#endif
