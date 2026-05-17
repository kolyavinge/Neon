#pragma warning(push)
#pragma warning(disable : 5039 4668)
#include <windows.h>
#pragma warning(pop)
#include <common/ProjectDirectories.h>

ProjectDirectories::ProjectDirectories() {
    _root.prepareEnoughCapacity(1024);
    GetCurrentDirectory(1024, _root.getWCharPointer());
    _shaders = _root;
    _shaders.append(L"shaders\\");
}

String& ProjectDirectories::getShaders() {
    return _shaders;
}
