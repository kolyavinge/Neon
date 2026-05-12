#include <debug/VehicleDebuger.h>
#include <lib/calc/UnitConverter.h>
#include <stdio.h>

void VehicleDebuger::printDebugInfo(Vehicle& vehicle) {
    printf("RPM: %i|", (int)vehicle.getEngine().getRpm());

    printf("Wh: %.2f|", vehicle.getDriveWheel(0).getAngularVelocity());

    printf("SR: %.2f (%.2f/%.2f) %.2f (%.2f/%.2f)|",
        vehicle.getDriveWheel(0).getSlipRatio().value,
        vehicle.getDriveWheel(0).getSlipRatio().drivenVelocity,
        vehicle.getDriveWheel(0).getSlipRatio().linearVelocity,
        vehicle.getNonDriveWheel(0).getSlipRatio().value,
        vehicle.getNonDriveWheel(0).getSlipRatio().drivenVelocity,
        vehicle.getNonDriveWheel(0).getSlipRatio().linearVelocity);

    printf("SA: %.1f %.1f %.1f %.1f|",
        UnitConverter::radiansToDegrees(vehicle.getNonDriveWheel(0).getSlipAngle()),
        UnitConverter::radiansToDegrees(vehicle.getNonDriveWheel(1).getSlipAngle()),
        UnitConverter::radiansToDegrees(vehicle.getDriveWheel(0).getSlipAngle()),
        UnitConverter::radiansToDegrees(vehicle.getDriveWheel(1).getSlipAngle()));

    printf("Lng: %i|",
        (int)vehicle.getDriveWheel(0).getLongitudinalForce().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getDriveWheel(0).getLongitudinalForce()) > 0.0f ? 1 : -1));

    printf("Lat: %i %i|",
        (int)vehicle.getNonDriveWheel(0).getLateralForce().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getNonDriveWheel(0).getLateralForce()) > 0.0f ? 1 : -1),
        (int)vehicle.getNonDriveWheel(1).getLateralForce().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getNonDriveWheel(1).getLateralForce()) > 0.0f ? 1 : -1)
    );

    printf("Spng: %i|", (int)vehicle.getSpring(0).getForce());

    printf("Velo: %.2f|",
        UnitConverter::msToKmh(vehicle.getLinearVelocity().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getLinearVelocity()) > 0.0f ? 1.0f : -1.0f)));

    printf("\r\n");
}
