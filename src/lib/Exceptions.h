#pragma once

#include <lib/Object.h>

class Exception : public Object {

public:
    wchar_t message[256];

    Exception();
    Exception(const wchar_t* msg);
};

class ArgumentException : public Exception {

public:
    ArgumentException();
    ArgumentException(const wchar_t* msg);
};

class ObjectStateException : public Exception {

public:
    ObjectStateException();
    ObjectStateException(const wchar_t* msg);
};

class IndexOutOfBoundsException : public Exception {

public:
    IndexOutOfBoundsException();
    IndexOutOfBoundsException(const wchar_t* msg);
};
