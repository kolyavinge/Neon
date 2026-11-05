#include <common/constants.h>
#include <engine/vehicle/GearboxLogic.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Gear.h>
#include <model/vehicle/VehicleData.h>

bool GearboxLogic::shift(Vehicle& vehicle) {
    if (vehicle.getGearbox().getKind() == GearboxKind::automatic) {
        return shiftAutomatic(vehicle);
    } else {
        return shiftManual(vehicle);
    }
}

bool GearboxLogic::shiftAutomatic(Vehicle& vehicle) {
    VehicleData& data = vehicle.getData();
    Engine& engine = vehicle.getEngine();
    Gearbox& gearbox = vehicle.getGearbox();
    DrivingInputData& drivingInputData = vehicle.getDrivingInputData();
    float sumSlipRatio = vehicle.getDriveWheel(0).getSlipRatio().value + vehicle.getDriveWheel(1).getSlipRatio().value;
    float averageSlipRatio = sumSlipRatio / (float)VehicleConstants::oneAxleWheelsCount;
    bool bothDriveWheelsHaveGroundContact = vehicle.getDriveWheel(0).hasGroundContact() && vehicle.getDriveWheel(1).hasGroundContact();
    float throttleRatio = drivingInputData.getThrottleRatio();
    bool isAccelerating = throttleRatio > 0.0f;
    if (isAccelerating && !gearbox.isClutchActive()) {
        gearbox.activateClutch();
    }
    if (isAccelerating && bothDriveWheelsHaveGroundContact && engine.getRpm() > data.autoUpShiftRpm && averageSlipRatio < data.optimalSlipRatio) {
        return gearbox.shiftUp();
    } else if (isAccelerating && gearbox.getCurrentGear() < Gear::first) {
        return gearbox.shiftUp();
    } else if (!isAccelerating && engine.getRpm() == data.engineMinRpm) {
        if (gearbox.getCurrentGear() >= Gear::first) {
            return gearbox.shiftDown();
        }
    } else if (getRpmOnLowerGear(engine, gearbox) < data.autoDownShiftRpm) {
        if (gearbox.getCurrentGear() > Gear::first) {
            return gearbox.shiftDown();
        }
    }

    return false;
}

float GearboxLogic::getRpmOnLowerGear(Engine& engine, Gearbox& gearbox) {
    // какие были бы обороты двигателя если бы мы переключились на передачу ниже
    if (gearbox.getCurrentGearRatio() != 0.0f) {
        return engine.getRpm() * gearbox.getLowerGearRatio() / gearbox.getCurrentGearRatio();
    } else {
        return 0.0f;
    }
}

bool GearboxLogic::shiftManual(Vehicle& vehicle) {
    VehicleData& data = vehicle.getData();
    Engine& engine = vehicle.getEngine();
    Gearbox& gearbox = vehicle.getGearbox();
    DrivingInputData& drivingInputData = vehicle.getDrivingInputData();
    float throttleRatio = drivingInputData.getThrottleRatio();
    if (throttleRatio > 0.0f && !gearbox.isClutchActive()) {
        gearbox.activateClutch();
    } else if (throttleRatio == 0.0f && engine.getRpm() == data.engineMinRpm && gearbox.isClutchActive()) {
        gearbox.deactivateClutch();
    }
    if (drivingInputData.isShiftedUp()) {
        return gearbox.shiftUp();
    } else if (drivingInputData.isShiftedDown()) {
        return gearbox.shiftDown();
    }

    return false;
}
