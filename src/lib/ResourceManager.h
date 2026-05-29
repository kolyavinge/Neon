#pragma once

#include <lib/system.h>

class ResourceException : public Exception {
};

class ResourceManager : public Object {

public:
    String getTextFileContent(int resourceFileId);
};
