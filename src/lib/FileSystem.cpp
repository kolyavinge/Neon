#include <lib/FileSystem.h>
#include <lib/windows.h>

FileNotFoundException::FileNotFoundException(const wchar_t* fileName) :
    Exception(fileName) {
}

DirectoryNotFoundException::DirectoryNotFoundException(const wchar_t* directoryName) :
    Exception(directoryName) {
}

bool FileSystem::fileExists(String& filePath) {
    DWORD attrib = GetFileAttributes(filePath.getWCharPointer());
    return attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY);
}

bool FileSystem::directoryExists(String& directoryPath) {
    DWORD attributes = GetFileAttributes(directoryPath.getWCharPointer());
    if (attributes != INVALID_FILE_ATTRIBUTES &&
        (attributes & FILE_ATTRIBUTE_DIRECTORY)) {
        return true;
    }

    return false;
}

void FileSystem::readByteFile(String& filePath, output List<char>& fileContent) {
    HANDLE file = CreateFile(filePath.getWCharPointer(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) throw FileNotFoundException(filePath.getWCharPointer());
    int fileSize = (int)GetFileSize(file, NULL);
    fileContent.prepareEnoughCapacity(fileSize);
    DWORD bytesRead;
    if (ReadFile(file, fileContent.getItemsPointer(), (DWORD)fileSize, &bytesRead, NULL)) {
        CloseHandle(file);
    } else {
        throw IOException(L"Cannot read the file.");
    }
}

void FileSystem::readTextFile(String& filePath, output String& fileContent) {
    HANDLE file = CreateFile(filePath.getWCharPointer(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) throw FileNotFoundException(filePath.getWCharPointer());
    int fileSize = (int)GetFileSize(file, NULL);
    fileContent.prepareEnoughCapacity(fileSize + 1);
    List<char> buffer(fileSize);
    DWORD bytesRead;
    if (ReadFile(file, buffer.getItemsPointer(), (DWORD)fileSize, &bytesRead, NULL)) {
        int wcharCount = MultiByteToWideChar(CP_UTF8, 0, buffer.getItemsPointer(), (int)bytesRead, NULL, 0);
        MultiByteToWideChar(CP_UTF8, 0, buffer.getItemsPointer(), (int)bytesRead, fileContent.getWCharPointer(), wcharCount);
        fileContent.append(L"\0");
        CloseHandle(file);
    } else {
        throw IOException(L"Cannot read the file.");
    }
}

void FileSystem::getFilesInDirectory(String& directoryPath, output List<String>& files) {
    String filter(L"*");
    getFilesInDirectoryByFilter(directoryPath, filter, output files);
}

void FileSystem::getFilesInDirectoryByFilter(String& directoryPath, String& filter, output List<String>& files) {
    String directoryPathAndFilter(directoryPath);
    if (!directoryPathAndFilter.endsWith(L"\\")) {
        directoryPathAndFilter.append(L"\\");
    }
    directoryPathAndFilter.append(filter);
    WIN32_FIND_DATAW findData;
    HANDLE find = FindFirstFile(directoryPathAndFilter.getWCharPointer(), &findData);
    String fileName;
    if (find == INVALID_HANDLE_VALUE) return;
    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
            wcscmp(findData.cFileName, L".") != 0 &&
            wcscmp(findData.cFileName, L"..") != 0) {
            fileName = findData.cFileName;
            files.add(fileName);
        }
    } while (FindNextFile(find, &findData) != 0);
    FindClose(find);
}
