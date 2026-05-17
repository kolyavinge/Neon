#include <common/ProjectDirectories.h>
#include <core/di/CommonInjectModule.h>
#include <lib/FileSystem.h>

void CommonInjectModule::init(Binder& binder) {
    binder.bindSingleton<ProjectDirectories>();
    binder.bindSingleton<FileSystem>();
}
