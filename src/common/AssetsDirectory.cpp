#include <common/AssetsDirectory.h>
#include <lib/FileSystem.h>
#include <lib/Path.h>

AssetsDirectory::AssetsDirectory(
    Environment& environment,
    FileSystem& fileSystem) :
    _fileSystem(fileSystem) {
    _assets = environment.getCurrentDirectory();
    findAssetsDirectory();
    _models3d = _assets;
    _models3d.append(L"\\models3d\\");
}

String& AssetsDirectory::getModels3d() {
    return _models3d;
}

void AssetsDirectory::findAssetsDirectory() {
    _assets.append(L"\\assets");
    while (_assets.getLength() > 0 && !_fileSystem.directoryExists(_assets)) {
        _assets = Path::getDirectoryPath(_assets); // remove assets
        _assets = Path::getDirectoryPath(_assets); // remove parent
        if (_assets.getLength() == 0) throw DirectoryNotFoundException(L"assets");
        _assets.append(L"\\assets");
    }
}
