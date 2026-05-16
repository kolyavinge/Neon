#include <lib/exceptions.h>
#include <string>

Exception::Exception() {
    memset(message, 0, 256 * sizeof(wchar_t));
}

Exception::Exception(const wchar_t* msg) {
    wcscpy_s(message, 256, msg);
}

ArgumentException::ArgumentException() {}

ArgumentException::ArgumentException(const wchar_t* msg) :Exception(msg) {}

ObjectStateException::ObjectStateException() {}

ObjectStateException::ObjectStateException(const wchar_t* msg) :Exception(msg) {}

IndexOutOfBoundsException::IndexOutOfBoundsException() {}

IndexOutOfBoundsException::IndexOutOfBoundsException(const wchar_t* msg) :Exception(msg) {}

IOException::IOException() {}

IOException::IOException(const wchar_t* msg) :Exception(msg) {}
