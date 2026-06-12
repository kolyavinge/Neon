#include <debug/VehicleDebuger.h>
#include <lib/calc/UnitConverter.h>
#include <stdio.h>

int VehicleDebuger::_tick = 0;

void VehicleDebuger::printDebugInfo(Vehicle& vehicle, DrivingInputData& inputData) {
    _tick++;
    if ((_tick % 10) != 0) return;

    printGear(vehicle);
    printThrottle(inputData);
    printEngineRpm(vehicle);
    printWheelAngularVelocity(vehicle);
    printDiffBetweenRpmAndAngularVelocity(vehicle);
    printSlipRatio(vehicle, true);
    //printSlipAngle(vehicle);
    //printLongitudinalForce(vehicle);
    //printLateralForce(vehicle);
    printVehicleLinearVelocity(vehicle);
    //printVehicleAngularVelocity(vehicle);
    //printWheelLoadWeight(vehicle);
    //printSpringForce(vehicle);
    //printBodyAngles(vehicle);

    printf("\r\n");
}

void VehicleDebuger::printGear(Vehicle& vehicle) {
    printf("Gr: %i|", (int)vehicle.getGearbox().getCurrentGear());
}

void VehicleDebuger::printThrottle(DrivingInputData& inputData) {
    printf("Th: %.2f|", inputData.getThrottleRatio());
}

void VehicleDebuger::printEngineRpm(Vehicle& vehicle) {
    printf("RPM: %i|", (int)vehicle.getEngine().getRpm());
}

void VehicleDebuger::printWheelAngularVelocity(Vehicle& vehicle) {
    printf("Wh: %i|", (int)vehicle.getDriveWheel(0).getAngularVelocity());
}

void VehicleDebuger::printDiffBetweenRpmAndAngularVelocity(Vehicle& vehicle) {
    float diff = vehicle.getEngine().getRpm() - UnitConverter::angularVelocityToRpm(vehicle.getDriveWheel(0).getAngularVelocity()) * vehicle.getGearbox().getCurrentGearRatio();
    printf("Df: %i|", (int)diff);
}

void VehicleDebuger::printSlipRatio(Vehicle& vehicle, bool onlyDriveWheels) {
    if (onlyDriveWheels) {
        printf("SR: %.2f (%.2f/%.2f)|",
            vehicle.getDriveWheel(0).getSlipRatio().value,
            vehicle.getDriveWheel(0).getSlipRatio().drivenVelocity,
            vehicle.getDriveWheel(0).getSlipRatio().linearVelocity);
    } else {
        printf("SR: %.2f (%.2f/%.2f) %.2f (%.2f/%.2f)|",
            vehicle.getDriveWheel(0).getSlipRatio().value,
            vehicle.getDriveWheel(0).getSlipRatio().drivenVelocity,
            vehicle.getDriveWheel(0).getSlipRatio().linearVelocity,
            vehicle.getNonDriveWheel(0).getSlipRatio().value,
            vehicle.getNonDriveWheel(0).getSlipRatio().drivenVelocity,
            vehicle.getNonDriveWheel(0).getSlipRatio().linearVelocity);
    }
}

void VehicleDebuger::printSlipAngle(Vehicle& vehicle) {
    printf("SA: %.1f %.1f %.1f %.1f|",
        UnitConverter::radiansToDegrees(vehicle.getNonDriveWheel(0).getSlipAngle()),
        UnitConverter::radiansToDegrees(vehicle.getNonDriveWheel(1).getSlipAngle()),
        UnitConverter::radiansToDegrees(vehicle.getDriveWheel(0).getSlipAngle()),
        UnitConverter::radiansToDegrees(vehicle.getDriveWheel(1).getSlipAngle()));
}

void VehicleDebuger::printLongitudinalForce(Vehicle& vehicle) {
    printf("Lng: %i|",
        (int)vehicle.getDriveWheel(0).getLongitudinalForce().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getDriveWheel(0).getLongitudinalForce()) > 0.0f ? 1 : -1));
}

void VehicleDebuger::printLateralForce(Vehicle& vehicle) {
    printf("Lat: %i %i|",
        (int)vehicle.getNonDriveWheel(0).getLateralForce().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getNonDriveWheel(0).getLateralForce()) > 0.0f ? 1 : -1),
        (int)vehicle.getNonDriveWheel(1).getLateralForce().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getNonDriveWheel(1).getLateralForce()) > 0.0f ? 1 : -1)
    );
}

void VehicleDebuger::printVehicleLinearVelocity(Vehicle& vehicle) {
    float v = UnitConverter::msToKmh(vehicle.getLinearVelocity().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getLinearVelocity()) > 0.0f ? 1.0f : -1.0f));
    printf("Linear: %i|", (int)v);
}

void VehicleDebuger::printVehicleAngularVelocity(Vehicle& vehicle) {
    float v = vehicle.getLinearVelocity().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getLinearVelocity()) > 0.0f ? 1.0f : -1.0f) / vehicle.getDriveWheel(0).getRadius();
    printf("Angular V: %i|", (int)v);
}

void VehicleDebuger::printWheelLoadWeight(Vehicle& vehicle) {
    printf("Wheel weight: %i %i %i %i|",
        (int)vehicle.getWheel(0).getLoadWeight(),
        (int)vehicle.getWheel(1).getLoadWeight(),
        (int)vehicle.getWheel(2).getLoadWeight(),
        (int)vehicle.getWheel(3).getLoadWeight());
}

void VehicleDebuger::printSpringForce(Vehicle& vehicle) {
    printf("Spring: %i %i %i %i|",
        (int)vehicle.getSpring(0).getForce(),
        (int)vehicle.getSpring(1).getForce(),
        (int)vehicle.getSpring(2).getForce(),
        (int)vehicle.getSpring(3).getForce());
}

void VehicleDebuger::printBodyAngles(Vehicle& vehicle) {
    printf("Body pitch: %.2f|", UnitConverter::radiansToDegrees(vehicle.getBody().getAnglesRelateChassis().pitch));
    printf("Body roll: %.2f|", UnitConverter::radiansToDegrees(vehicle.getBody().getAnglesRelateChassis().roll));
}
