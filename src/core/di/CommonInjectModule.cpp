#include <core/InputManager.h>
#include <core/di/CommonInjectModule.h>

void CommonInjectModule::init(Binder& binder) {
    binder.bindSingleton<InputManager>();
}
