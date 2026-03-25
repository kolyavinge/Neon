#include <core/di/EngineInjectModule.h>
#include <engine/vehicle/VehicleForceLogic.h>
#include <engine/vehicle/VehiclePositionLogic.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <engine/vehicle/VehicleWeightTransferLogic.h>

void EngineInjectModule::init(Binder& binder) {
    binder.bindSingleton<VehicleForceLogic>(VehicleForceLogic::resolve);
    binder.bindSingleton<VehiclePositionLogic>(VehiclePositionLogic::resolve);
    binder.bindSingleton<VehicleUpdater>(VehicleUpdater::resolve);
    binder.bindSingleton<VehicleWeightTransferLogic>(VehicleWeightTransferLogic::resolve);
}
