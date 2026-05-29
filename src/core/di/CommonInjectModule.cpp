#include <common/AssetsDirectory.h>
#include <core/di/CommonInjectModule.h>
#include <lib/Environment.h>
#include <lib/FileSystem.h>
#include <lib/ResourceManager.h>

void CommonInjectModule::init(Binder& binder) {
    binder.bindSingleton<AssetsDirectory>(AssetsDirectory::resolve);
    binder.bindSingleton<Environment>();
    binder.bindSingleton<FileSystem>();
    binder.bindSingleton<ResourceManager>();
}
