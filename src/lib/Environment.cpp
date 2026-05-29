#include <lib/Environment.h>
#include <lib/Path.h>
#include <lib/windows.h>

String Environment::getCurrentDirectory() {
    wchar_t path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);
    String result = path;
    result = Path::getDirectoryPath(result);

    return result;
}
