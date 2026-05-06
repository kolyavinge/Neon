#include <core/di/EngineInjectModule.h>
#include <engine/GameUpdater.h>
#include <engine/vehicle/ForceLogic.h>
#include <engine/vehicle/PositionLogic.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <engine/vehicle/VelocityLogic.h>
#include <engine/vehicle/WeightTransferLogic.h>

void EngineInjectModule::init(Binder& binder) {
    binder.bindSingleton<GameUpdater>(GameUpdater::resolve);
    binder.bindSingleton<ForceLogic>();
    binder.bindSingleton<PositionLogic>();
    binder.bindSingleton<VehicleUpdater>(VehicleUpdater::resolve);
    binder.bindSingleton<VelocityLogic>();
    binder.bindSingleton<WeightTransferLogic>();
}
