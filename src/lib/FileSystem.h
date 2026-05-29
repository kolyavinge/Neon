#pragma once

#include <lib/system.h>

class FileNotFoundException : public Exception {

public:
    FileNotFoundException(const wchar_t* fileName);
};

class DirectoryNotFoundException : public Exception {

public:
    DirectoryNotFoundException(const wchar_t* directoryName);
};

class FileSystem : public Object {

public:
    bool fileExists(String& filePath);
    bool directoryExists(String& directoryPath);
    void readByteFile(String& filePath, output List<char>& fileContent);
    void readTextFile(String& filePath, output String& fileContent);
    void getFilesInDirectory(String& directoryPath, output List<String>& files);
    void getFilesInDirectoryByFilter(String& directoryPath, String& filter, output List<String>& files);
};
