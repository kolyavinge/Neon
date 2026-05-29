#pragma once

#include <lib/system.h>

class InvalidPathException : public Exception {};

class Path : public Object {

public:
    static String getDirectoryPath(String& path);
    static String getFileNameWithExtension(String& path);
    static String getFileNameWithoutExtension(String& path);
    static String getFileExtension(String& path);
};
