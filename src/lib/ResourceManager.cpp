#include <common/resource.h>
#include <lib/ResourceManager.h>
#include <lib/windows.h>

String ResourceManager::getTextFileContent(int resourceFileId) {
    HRSRC hRes = FindResource(nullptr, MAKEINTRESOURCE(resourceFileId), MAKEINTRESOURCE(TEXTFILE));
    if (!hRes) throw ResourceException();
    HGLOBAL hData = LoadResource(nullptr, hRes);
    if (!hData) throw ResourceException();
    char* pBuffer = (char*)LockResource(hData);
    String result(pBuffer, Encoding::utf8);

    return result;
}
