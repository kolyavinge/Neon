#include <debug/VehicleDebuger.h>
#include <lib/calc/UnitConverter.h>
#include <stdio.h>

void VehicleDebuger::printDebugInfo(Vehicle& vehicle) {
    //printEngineRpm(vehicle);
    //printWheelAngularVelocity(vehicle);
    //printSlipRatio(vehicle);
    //printSlipAngle(vehicle);
    //printLongitudinalForce(vehicle);
    //printLateralForce(vehicle);
    //printVehicleVelocity(vehicle);
    //printWheelLoadWeight(vehicle);
    printSpringForce(vehicle);
    printBodyAngles(vehicle);
    printf("\r\n");
}

void VehicleDebuger::printEngineRpm(Vehicle& vehicle) {
    printf("RPM: %i|", (int)vehicle.getEngine().getRpm());
}

void VehicleDebuger::printWheelAngularVelocity(Vehicle& vehicle) {
    printf("Wh: %.2f|", vehicle.getDriveWheel(0).getAngularVelocity());
}

void VehicleDebuger::printSlipRatio(Vehicle& vehicle) {
    printf("SR: %.2f (%.2f/%.2f) %.2f (%.2f/%.2f)|",
        vehicle.getDriveWheel(0).getSlipRatio().value,
        vehicle.getDriveWheel(0).getSlipRatio().drivenVelocity,
        vehicle.getDriveWheel(0).getSlipRatio().linearVelocity,
        vehicle.getNonDriveWheel(0).getSlipRatio().value,
        vehicle.getNonDriveWheel(0).getSlipRatio().drivenVelocity,
        vehicle.getNonDriveWheel(0).getSlipRatio().linearVelocity);
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

void VehicleDebuger::printVehicleVelocity(Vehicle& vehicle) {
    printf("Velo: %.2f|",
        UnitConverter::msToKmh(vehicle.getLinearVelocity().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getLinearVelocity()) > 0.0f ? 1.0f : -1.0f)));
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
    printf("Body pitch: %.2f|", UnitConverter::radiansToDegrees(vehicle.getBody().getAngles().pitch));
    printf("Body roll: %.2f|", UnitConverter::radiansToDegrees(vehicle.getBody().getAngles().roll));
}
