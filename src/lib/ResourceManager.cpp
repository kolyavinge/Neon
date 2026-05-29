#include <common/resource.h>
#include <lib/ResourceManager.h>
#include <lib/windows.h>

String ResourceManager::getTextFileContent(int resourceFileId) {
    HRSRC hRes = FindResource(nullptr, MAKEINTRESOURCE(resourceFileId), MAKEINTRESOURCE(TEXTFILE));
    if (!hRes) throw ResourceException();
    HGLOBAL hData = LoadResource(nullptr, hRes);
    if (!hData) throw ResourceException();
    char* pBuffer = (char*)LockResource(hData);
    int size = (int)SizeofResource(nullptr, hRes);
    int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, pBuffer, size, NULL, 0);
    wchar_t buf[1024] = {};
    MultiByteToWideChar(CP_UTF8, 0, pBuffer, size, buf, sizeNeeded);

    return String(buf);
}
