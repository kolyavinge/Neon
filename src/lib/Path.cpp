#include <lib/Path.h>

String Path::getDirectoryPath(String& path) {
    int slash = path.lastIndexOf(L'\\');
    if (slash == -1) return L"";
    String result = path.substring(0, slash);

    return result;
}

String Path::getFileNameWithExtension(String& path) {
    int slash = path.lastIndexOf(L'\\');
    if (slash == -1) throw InvalidPathException();
    String result = path.substring(slash + 1, path.getLength() - slash - 1);

    return result;
}

String Path::getFileNameWithoutExtension(String& path) {
    int slash = path.lastIndexOf(L'\\');
    if (slash == -1) throw InvalidPathException();
    int dot = path.lastIndexOf(L'.');
    if (dot == -1) throw InvalidPathException();
    String result = path.substring(slash + 1, dot - slash - 1);

    return result;
}

String Path::getFileExtension(String& path) {
    int dot = path.lastIndexOf(L'.');
    if (dot == -1) throw InvalidPathException();
    String result = path.substring(dot + 1, path.getLength() - dot - 1);

    return result;
}
