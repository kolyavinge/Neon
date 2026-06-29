#include <engine/vehicle/GearboxLogic.h>
#include <model/vehicle/Gear.h>
#include <model/vehicle/VehicleData.h>

bool GearboxLogic::shift(Vehicle& vehicle, DrivingInputData& drivingInputData) {
    if (vehicle.getGearbox().getKind() == GearboxKind::automatic) {
        return shiftAutomatic(vehicle, drivingInputData.getThrottleRatio());
    } else {
        return shiftManual(vehicle.getGearbox(), drivingInputData);
    }
}

bool GearboxLogic::shiftAutomatic(Vehicle& vehicle, float throttleRatio) {
    VehicleData& data = vehicle.getData();
    Engine& engine = vehicle.getEngine();
    Gearbox& gearbox = vehicle.getGearbox();
    bool isAccelerating = throttleRatio > 0.0f;
    if (isAccelerating && engine.getRpm() > data.autoShiftRpm) {
        return gearbox.shiftUp();
    } else if (isAccelerating && engine.getRpm() == data.engineMinRpm) {
        if (gearbox.getCurrentGear() == Gear::neutral) {
            return gearbox.shiftUp();
        }
    } else if (!isAccelerating && engine.getRpm() == data.engineMinRpm) {
        if (gearbox.getCurrentGear() == Gear::first) {
            return gearbox.shiftDown();
        }
    } else if (!isAccelerating && getRpmOnLowerGear(engine, gearbox) < data.autoShiftRpm) {
        if (gearbox.getCurrentGear() > Gear::first) {
            return gearbox.shiftDown();
        }
    }

    return false;
}

float GearboxLogic::getRpmOnLowerGear(Engine& engine, Gearbox& gearbox) {
    return engine.getRpm() * gearbox.getLowerGearRatio() / gearbox.getCurrentGearRatio();
}

bool GearboxLogic::shiftManual(Gearbox& gearbox, DrivingInputData& drivingInputData) {
    if (drivingInputData.isShiftedUp()) {
        return gearbox.shiftUp();
    } else if (drivingInputData.isShiftedDown()) {
        return gearbox.shiftDown();
    }

    return false;
}
