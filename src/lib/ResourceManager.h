#pragma once

#include <lib/system.h>

class ResourceException : public Exception {
};

class ResourceManager : public Object {

    List<char> _charBuf;

public:
    String getTextFileContent(int resourceFileId);
};
