#include <common/resource.h>
#include <lib/ResourceManager.h>
#include <lib/windows.h>

String ResourceManager::getTextFileContent(int resourceFileId) {
    HRSRC hRes = FindResource(nullptr, MAKEINTRESOURCE(resourceFileId), MAKEINTRESOURCE(TEXTFILE));
    if (!hRes) throw ResourceException();
    HGLOBAL hData = LoadResource(nullptr, hRes);
    if (!hData) throw ResourceException();
    char* pBuffer = (char*)LockResource(hData);
    int sizeInBytes = (int)SizeofResource(NULL, hRes);
    _charBuf.clear();
    _charBuf.addRange(pBuffer, sizeInBytes);
    _charBuf.add('\0');
    String result(_charBuf.getItemsPointer(), Encoding::utf8);

    return result;
}
