//  Header:     Str  (Dynamic Strings)
//  Version:    3.10
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides a general dynamic string class.
//
//  Written by: Scott Robert Ladd

#if !defined(__STRING_HPP)
#define __STRING_HPP 1

enum StrCompVal  {SC_LESS, SC_EQUAL, SC_GREATER, SC_ERROR};
enum StrCompMode {SM_SENSITIVE, SM_IGNORE};
enum StrError    {SE_ALLOC, SE_TOO_LONG};

class String
    {
    private:
        // instance variables
        unsigned int Siz;    // allocated size
        unsigned int Len;    // current length
        char * Txt;          // pointer to text

        // class constant
        static unsigned int AllocIncr;

        // pointer to exception handler
        static void (*ErrorHandler)(StrError err);

        // private method used to shrink string to minimum allocation
        void Shrink();

    public:
        // constructor
        String();
        String(const String & str);
        String(const char * cstr);
        String(char fillCh, unsigned int count);

        // destructor
        ~String();

        // value return methods
        unsigned int Length();
        unsigned int Size();

        // Assign an exception handler
        static void SetErrorHandler(void (* userHandler)(StrError));

        // create a c-string from String method
        operator const char * ();

        // assignment method
        void operator = (const String & str);

        // concatenation methods
        friend String operator + (const String & str1, const String & str2);
        void operator += (const String & str);

        // comparison methods
        int operator <  (const String & str);
        int operator >  (const String & str);
        int operator <= (const String & str);
        int operator >= (const String & str);
        int operator == (const String & str);
        int operator != (const String & str);

        StrCompVal Compare(const String & str, StrCompMode caseChk= SM_IGNORE);

        // substring search methods
        int Find(const String & str, unsigned int & pos,
                 StrCompMode caseChk = SM_IGNORE);

        // substring deletion method
        void Delete(unsigned int pos, unsigned int count);

        // substring insertion methods
        void Insert(unsigned int pos, char ch);
        void Insert(unsigned int pos, const String & str);

        // substring retrieval method
        String SubStr(unsigned int start, unsigned int count);

        // character retrieval method
        char operator [] (unsigned int pos);

        // case-modification methods
        String ToUpper();
        String ToLower();
    };

// value return methods
inline unsigned int String::Length()
    {
    return Len;
    }

inline unsigned int String::Size()
    {
    return Siz;
    }

// comparison methods
inline int String::operator <  (const String & str)
    {
    return (Compare(str) == SC_LESS);
    }

inline int String::operator >  (const String & str)
    {
    return (Compare(str) == SC_GREATER);
    }

inline int String::operator <= (const String & str)
    {
    return (Compare(str) != SC_GREATER);
    }

inline int String::operator >= (const String & str)
    {
    return (Compare(str) != SC_LESS);
    }

inline int String::operator == (const String & str)
    {
    return (Compare(str) == SC_EQUAL);
    }

inline int String::operator != (const String & str)
    {
    return (Compare(str) != SC_EQUAL);
    }

// character retrieval method
inline char String::operator [] (unsigned int pos)
    {
    if (pos >= Len)
        return '\x00';
    else
        return Txt[pos];
    }

#endif
