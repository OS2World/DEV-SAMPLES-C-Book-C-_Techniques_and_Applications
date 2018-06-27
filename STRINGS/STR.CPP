//  Module:     Str  (Dynamic Strings)
//  Version:    3.10
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides a general dynamic string class.
//
//  Written by: Scott Robert Ladd

#include "Str.hpp"

extern "C"
    {
    #include "string.h"
    #include "stdio.h"
    #include "stdlib.h"
    #include "ctype.h"
    #include "limits.h"
    }

// prototype for default error handler
static void DefaultHandler(StrError err);

// class-global constant intialization
unsigned int String::AllocIncr = 8;
void (*(String::ErrorHandler))(StrError) = DefaultHandler;

// default exception handler
static void DefaultHandler(StrError err)
    {
    printf("\aERROR in String object: ");

    switch (err)
        {
        case SE_ALLOC :
            printf("memory allocation failure");
            break;
        case SE_TOO_LONG :
            printf("exceeded %d character limit",UINT_MAX);
        }

    printf("\n");

    exit(1);
    }

// private function to shrink the size of an allocated string
void String::Shrink()
    {
    char * temp;

    if ((Siz - Len) > AllocIncr)
        {
        Siz  = ((Len + AllocIncr) / AllocIncr) * AllocIncr;

        temp = new char [Siz];

        if (temp != NULL)
            {
            strcpy(temp,Txt);
            delete Txt;
            Txt  = temp;
            }
        else
            ErrorHandler(SE_ALLOC);
        }
    }

// constructor
String::String()
    {
    Len = 0;
    Siz = AllocIncr;

    Txt = new char[Siz];

    if (Txt == NULL)
        ErrorHandler(SE_ALLOC);

    Txt[0] = '\x00';
    }

String::String(const String & str)
    {
    Len = str.Len;
    Siz = str.Siz;

    Txt = new char[Siz];

    if (Txt == NULL)
        ErrorHandler(SE_ALLOC);

    strcpy(Txt,str.Txt);
    }

String::String(const char * cstr)
    {
    if ((cstr == NULL) || (cstr[0] == '\x00'))
        {
        Len = 0;
        Siz = AllocIncr;
        }
    else
        {
        Len = strlen(cstr);
        Siz = ((Len + AllocIncr) / AllocIncr) * AllocIncr;
        }

    Txt = new char [Siz];

    if (Txt == NULL)
        ErrorHandler(SE_ALLOC);

    if (Len > 0)
        strcpy(Txt,cstr);
    else
        Txt[0] = '\x00';
    }

String::String(char fillCh, unsigned int count)
    {
    Siz = ((count + AllocIncr) / AllocIncr) * AllocIncr;
    Len = Siz;

    Txt = new char[Siz];

    if (Txt == NULL)
        ErrorHandler(SE_ALLOC);

    memset(Txt,fillCh,count);

    Txt[count] = '\x00';
    }

// destructor
String::~String()
    {
    delete Txt;
    }

// Assign an exception handler
void String::SetErrorHandler(void (* userHandler)(StrError))
    {
    ErrorHandler = userHandler;
    }

// create a c-string from String method
String::operator const char * ()
    {
    return Txt;
    }

// assignment method
void String::operator = (const String & str)
    {
    Len = str.Len;
    Siz = str.Siz;

    delete Txt;

    Txt = new char[Siz];

    if (Txt == NULL)
        ErrorHandler(SE_ALLOC);

    strcpy(Txt,str.Txt);
    }

// concatenation methods
String operator + (const String & str1, const String & str2)
    {
    unsigned long totalLen;
    unsigned int newLen, newSiz;
    String tempStr;
    char * temp;

    totalLen = str1.Len + str2.Len;

    if (totalLen > UINT_MAX)
        String::ErrorHandler(SE_TOO_LONG);

    newLen  = (unsigned int)totalLen;

    newSiz  = str1.Siz + str2.Siz;

    temp = new char[newSiz];

    if (temp == NULL)
        String::ErrorHandler(SE_ALLOC);

    strcpy(temp,str1.Txt);

    strcpy(&temp[str1.Len],str2.Txt);

    tempStr = temp;

    return tempStr;
    }

void String::operator += (const String & str)
    {
    unsigned long totalLen;
    unsigned int newLen, newSiz;
    char * temp;

    totalLen = str.Len + Len;

    if (totalLen > UINT_MAX)
        ErrorHandler(SE_TOO_LONG);

    newLen  = (unsigned int)totalLen;
    newSiz  = Siz + str.Siz;

    temp = new char[newSiz];

    if (temp == NULL)
        ErrorHandler(SE_ALLOC);

    strcpy(temp,Txt);

    delete Txt;

    Txt = temp;

    strcpy(&Txt[Len],str.Txt);

    Len = newLen;
    Siz = newSiz;

    Shrink();
    }

StrCompVal String::Compare(const String & str, StrCompMode caseChk)
    {
    char * tempStr1, * tempStr2;
    StrCompVal compVal;

    tempStr1 = strdup(Txt);

    if (tempStr1 == NULL)
        ErrorHandler(SE_ALLOC);

    tempStr2 = strdup(str.Txt);

    if (tempStr2 == NULL)
        ErrorHandler(SE_ALLOC);

    if (caseChk == SM_IGNORE)
        {
        strupr(tempStr1);
        strupr(tempStr2);
        }

    switch (strcmp(tempStr1,tempStr2))
        {
        case -1:
            compVal = SC_LESS;
            break;
        case 0:
            compVal = SC_EQUAL;
            break;
        case 1:
            compVal = SC_GREATER;
            break;
        default:
            compVal = SC_ERROR;
        }

    delete tempStr1;
    delete tempStr2;

    return compVal;
    }

// substring search methods
int String::Find(const String & str, unsigned int & pos, StrCompMode caseChk)
    {
    char * tempStr1, * tempStr2;
    unsigned int lastPos, searchLen, tempPos;
    int found;

    tempStr1 = strdup(Txt);

    if (tempStr1 == NULL)
        ErrorHandler(SE_ALLOC);

    tempStr2 = strdup(str.Txt);

    if (tempStr2 == NULL)
        ErrorHandler(SE_ALLOC);

    if (caseChk == SM_IGNORE)
        {
        strupr(tempStr1);
        strupr(tempStr2);
        }

    pos     = 0;
    tempPos = 0;
    found   = 0;

    searchLen = str.Len;
    lastPos   = Len - searchLen;

    while ((tempPos <= lastPos) && !found)
        {
        if (0 == strncmp(&tempStr1[tempPos],tempStr2,searchLen))
            {
            pos   = tempPos;
            found = 1;
            }
        else
            ++tempPos;
        }

    delete tempStr1;
    delete tempStr2;

    return found;
    }

// substring deletion method
void String::Delete(unsigned int pos, unsigned int count)
    {
    unsigned int copyPos;

    if (pos > Len)
        return;

    copyPos = pos + count;

    if (copyPos >= Len)
        Txt[pos] = 0;
    else
        while (copyPos <= Len + 1)
            {
            Txt[pos] = Txt[copyPos];
            ++pos;
            ++copyPos;
            }

    Len -= count;

    Shrink();
    }

// substring insertion methods
void String::Insert(unsigned int pos, char ch)
    {
    char * temp;

    if (pos > Len)
        return;

    if (Len + 1 == Siz)
        {
        Siz  += AllocIncr;
        temp  = new char[Siz];

        if (temp == NULL)
            ErrorHandler(SE_ALLOC);

        strcpy(temp,Txt);

        delete Txt;

        Txt = temp;
        }

    for (unsigned int col = Len + 1; col > pos; --col)
        Txt[col] = Txt[col-1];

    Txt[pos] = ch;

    ++Len;

    Txt[Len + 1] = '\x00';
    }

void String::Insert(unsigned int pos, const String & str)
    {
    unsigned long totalLen = str.Len + Len;

    if (totalLen > UINT_MAX)
        ErrorHandler(SE_TOO_LONG);

    unsigned int SLen = str.Len;

    if (SLen > 0)
        for (unsigned int i = 0; i < SLen; ++i)
            {
            Insert(pos,str.Txt[i]);
            ++pos;
            }
    }

// substring retrieval method
String String::SubStr(unsigned int start, unsigned int count)
    {
    String tempStr;
    char * temp;

    if ((start < Len) && (count > 0))
        {
        temp = new char [count + 1];

        memcpy(temp,&Txt[start],count);

        temp[count] = '\x00';
        }
    else
        temp = "";

    tempStr = temp;

    delete temp;

    return tempStr;
    }

// case-modification methods
String String::ToUpper()
    {
    String tempStr = *this;

    strupr(tempStr.Txt);

    return tempStr;
    }

String String::ToLower()
    {
    String tempStr = *this;

    strlwr(tempStr.Txt);

    return tempStr;
    }
