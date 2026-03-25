#pragma once

#include <lib/Object.h>

class Exception : public Object {};

class ArgumentException : public Exception {};

class ObjectStateException : public Exception {};

class IndexOutOfBoundsException : public Exception {};
