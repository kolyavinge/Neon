#include <core/di/EngineInjectModule.h>
#include <engine/GameUpdater.h>
#include <engine/vehicle/ForceLogic.h>
#include <engine/vehicle/GearboxLogic.h>
#include <engine/vehicle/PositionLogic.h>
#include <engine/vehicle/SteeringLogic.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <engine/vehicle/VelocityLogic.h>
#include <engine/vehicle/WeightTransferLogic.h>
#include <engine/vehicle/WheelLogic.h>

void EngineInjectModule::init(Binder& binder) {
    binder.bindSingleton<GameUpdater>(GameUpdater::resolve);
    binder.bindSingleton<ForceLogic>();
    binder.bindSingleton<GearboxLogic>();
    binder.bindSingleton<PositionLogic>(PositionLogic::resolve);
    binder.bindSingleton<SteeringLogic>(SteeringLogic::resolve);
    binder.bindSingleton<VehicleUpdater>(VehicleUpdater::resolve);
    binder.bindSingleton<VelocityLogic>();
    binder.bindSingleton<WeightTransferLogic>();
    binder.bindSingleton<WheelLogic>();
}
