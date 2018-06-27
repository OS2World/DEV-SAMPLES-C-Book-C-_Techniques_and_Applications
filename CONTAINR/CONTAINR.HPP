//  Header:     Containr (Abstract Base Class for Containers)
//  Version:    3.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides an abstract base class for container classes.
//
//  Written by: Scott Robert Ladd

#if !defined(__CONTAINR_HPP)
#define __CONTAINR_HPP 1

class Container
    {
    protected:
        // number of items in this list
        unsigned long Count;

        // pointer to exception handler
        void (* ErrorHandler)();

    public:
        // constructor
        Container();

        // copy constructor
        Container(const Container & c);

        // assignment opeartor
        void operator = (const Container & c);

        // store an item
        virtual int Store(void * item) = 0;

        // examine an item
        virtual void * Examine() = 0;

        // retrieve an item
        virtual void * Retrieve() = 0;

        // eliminate contents
        virtual void Empty() = 0;

        // return number of items in a container
        unsigned long GetCount()
            {
            return Count;
            }

        // set function for exception handler
        void AssignHandler(void (* userHandler)())
            {
            ErrorHandler = userHandler;
            }
    };

#endif
