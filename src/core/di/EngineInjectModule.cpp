#include <core/di/EngineInjectModule.h>
#include <engine/GameUpdater.h>
#include <engine/vehicle/VehicleForceLogic.h>
#include <engine/vehicle/VehiclePositionLogic.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <engine/vehicle/VehicleVelocityLogic.h>
#include <engine/vehicle/VehicleWeightTransferLogic.h>

void EngineInjectModule::init(Binder& binder) {
    binder.bindSingleton<GameUpdater>(GameUpdater::resolve);
    binder.bindSingleton<VehicleForceLogic>();
    binder.bindSingleton<VehiclePositionLogic>();
    binder.bindSingleton<VehicleUpdater>(VehicleUpdater::resolve);
    binder.bindSingleton<VehicleVelocityLogic>();
    binder.bindSingleton<VehicleWeightTransferLogic>();
}
