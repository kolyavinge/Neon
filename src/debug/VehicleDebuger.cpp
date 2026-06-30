#include <debug/VehicleDebuger.h>
#include <iostream>
#include <lib/calc/UnitConverter.h>
#include <stdio.h>

int VehicleDebuger::_tick = 0;

void VehicleDebuger::printDebugInfo(Vehicle& vehicle, DrivingInputData& inputData) {
    _tick++;
    if ((_tick % 10) != 0) return;

    paintText(inputData);
    printGear(vehicle);
    //printThrottle(inputData);
    printEngineRpm(vehicle);
    printWheelAngularVelocity(vehicle);
    //printDiffBetweenRpmAndAngularVelocity(vehicle);
    printSlipRatio(vehicle, inputData.getThrottleRatio(), inputData.getBrakeRatio(), false);
    //printSlipAngle(vehicle);
    //printLongitudinalForce(vehicle);
    //printLateralForce(vehicle);
    //printVehicleLinearVelocity(vehicle);
    //printVehicleAngularVelocity(vehicle);
    //printWheelLoadWeight(vehicle);
    //printSpringForce(vehicle);
    //printBodyAngles(vehicle);

    printf("\r\n");
}

void VehicleDebuger::printGear(Vehicle& vehicle) {
    printf("Gr %i|", (int)vehicle.getGearbox().getCurrentGear());
}

void VehicleDebuger::printThrottle(DrivingInputData& inputData) {
    printf("Th %.2f|", inputData.getThrottleRatio());
}

void VehicleDebuger::printEngineRpm(Vehicle& vehicle) {
    printf("RPM %i|", (int)vehicle.getEngine().getRpm());
}

void VehicleDebuger::printWheelAngularVelocity(Vehicle& vehicle) {
    printf("Wh %i|", (int)vehicle.getDriveWheel(0).getAngularVelocity());
}

void VehicleDebuger::printDiffBetweenRpmAndAngularVelocity(Vehicle& vehicle) {
    float diff = vehicle.getEngine().getRpm() - UnitConverter::angularVelocityToRpm(vehicle.getDriveWheel(0).getAngularVelocity()) * vehicle.getGearbox().getCurrentGearRatio();
    printf("Df %i|", (int)diff);
}

void VehicleDebuger::printSlipRatio(Vehicle& vehicle, float throttleRatio, float brakeRatio, bool onlyDriveWheels) {
    Vector3& chassisFrontNormal = vehicle.getChassis().getFrontNormal();
    if (onlyDriveWheels) {
        printf("SR %.2f(%.2f %.2f)|",
            vehicle.getDriveWheel(0).getSlipRatio(chassisFrontNormal, throttleRatio, brakeRatio).value,
            vehicle.getDriveWheel(0).getSlipRatio(chassisFrontNormal, throttleRatio, brakeRatio).drivenVelocity,
            vehicle.getDriveWheel(0).getSlipRatio(chassisFrontNormal, throttleRatio, brakeRatio).linearVelocity);
    } else {
        printf("SR %.2f(%.2f %.2f) %.2f(%.2f %.2f)|",
            vehicle.getNonDriveWheel(0).getSlipRatio(chassisFrontNormal, throttleRatio, brakeRatio).value,
            vehicle.getNonDriveWheel(0).getSlipRatio(chassisFrontNormal, throttleRatio, brakeRatio).drivenVelocity,
            vehicle.getNonDriveWheel(0).getSlipRatio(chassisFrontNormal, throttleRatio, brakeRatio).linearVelocity,
            vehicle.getDriveWheel(0).getSlipRatio(chassisFrontNormal, throttleRatio, brakeRatio).value,
            vehicle.getDriveWheel(0).getSlipRatio(chassisFrontNormal, throttleRatio, brakeRatio).drivenVelocity,
            vehicle.getDriveWheel(0).getSlipRatio(chassisFrontNormal, throttleRatio, brakeRatio).linearVelocity);
    }
}

void VehicleDebuger::printSlipAngle(Vehicle& vehicle) {
    printf("SA %.1f %.1f %.1f %.1f|",
        UnitConverter::radiansToDegrees(vehicle.getNonDriveWheel(0).getSlipAngle()),
        UnitConverter::radiansToDegrees(vehicle.getNonDriveWheel(1).getSlipAngle()),
        UnitConverter::radiansToDegrees(vehicle.getDriveWheel(0).getSlipAngle()),
        UnitConverter::radiansToDegrees(vehicle.getDriveWheel(1).getSlipAngle()));
}

void VehicleDebuger::printLongitudinalForce(Vehicle& vehicle) {
    Vector3& chassisFrontNormal = vehicle.getChassis().getFrontNormal();
    Wheel& frontLeftWheel = vehicle.getWheel(WheelPosition::frontLeft);
    Wheel& frontRightWheel = vehicle.getWheel(WheelPosition::frontRight);
    Wheel& rearLeftWheel = vehicle.getWheel(WheelPosition::rearLeft);
    Wheel& rearRightWheel = vehicle.getWheel(WheelPosition::rearRight);
    printf("Lng ");
    printLongitudinalForce(frontLeftWheel, chassisFrontNormal);
    printLongitudinalForce(frontRightWheel, chassisFrontNormal);
    printLongitudinalForce(rearLeftWheel, chassisFrontNormal);
    printLongitudinalForce(rearRightWheel, chassisFrontNormal, true);
    printf("|");
}

void VehicleDebuger::printLongitudinalForce(Wheel& wheel, Vector3& chassisFrontNormal, bool last) {
    if (wheel.getLongitudinalForce().getLength() == wheel.getLongitudinalForceBeforeNormalize()) {
        printf("%i",
            (int)(wheel.getLongitudinalForce().getLength() * Numeric::getSign(chassisFrontNormal.dotProduct(wheel.getLongitudinalForce()))));
    } else {
        printf("%i(%i)",
            (int)(wheel.getLongitudinalForce().getLength() * Numeric::getSign(chassisFrontNormal.dotProduct(wheel.getLongitudinalForce()))),
            (int)wheel.getLongitudinalForceBeforeNormalize());
    }
    if (!last) printf(" ");
}

void VehicleDebuger::printLateralForce(Vehicle& vehicle) {
    Wheel& frontLeftWheel = vehicle.getWheel(WheelPosition::frontLeft);
    Wheel& frontRightWheel = vehicle.getWheel(WheelPosition::frontRight);
    Wheel& rearLeftWheel = vehicle.getWheel(WheelPosition::rearLeft);
    Wheel& rearRightWheel = vehicle.getWheel(WheelPosition::rearRight);
    printf("Lat ");
    printLateralForce(frontLeftWheel);
    printLateralForce(frontRightWheel);
    printLateralForce(rearLeftWheel);
    printLateralForce(rearRightWheel, true);
    printf("|");
}

void VehicleDebuger::printLateralForce(Wheel& wheel, bool last) {
    if (wheel.getLateralForce().getLength() == wheel.getLateralForceBeforeNormalize()) {
        printf("%i", (int)(wheel.getLateralForce().getLength()));
    } else {
        printf("%i(%i)", (int)(wheel.getLateralForce().getLength()), (int)wheel.getLateralForceBeforeNormalize());
    }
    if (!last) printf(" ");
}

void VehicleDebuger::printVehicleLinearVelocity(Vehicle& vehicle) {
    float v = UnitConverter::msToKmh(vehicle.getLinearVelocity().getLength() * Numeric::getSign(vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getLinearVelocity())));
    printf("V %i|", (int)v);
}

void VehicleDebuger::printVehicleAngularVelocity(Vehicle& vehicle) {
    float v = vehicle.getLinearVelocity().getLength() * Numeric::getSign(vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getLinearVelocity())) / vehicle.getDriveWheel(0).getRadius();
    printf("AngV %i|", (int)v);
}

void VehicleDebuger::printWheelLoadWeight(Vehicle& vehicle) {
    printf("WheelWeight %i %i %i %i|",
        (int)vehicle.getWheel(0).getLoadWeight(),
        (int)vehicle.getWheel(1).getLoadWeight(),
        (int)vehicle.getWheel(2).getLoadWeight(),
        (int)vehicle.getWheel(3).getLoadWeight());
}

void VehicleDebuger::printSpringForce(Vehicle& vehicle) {
    printf("Spring %i %i %i %i|",
        (int)vehicle.getSpring(0).getForce(),
        (int)vehicle.getSpring(1).getForce(),
        (int)vehicle.getSpring(2).getForce(),
        (int)vehicle.getSpring(3).getForce());
}

void VehicleDebuger::printBodyAngles(Vehicle& vehicle) {
    printf("BodyPitch %.2f|", UnitConverter::radiansToDegrees(vehicle.getBody().getPitchAngleRelateChassis()));
    printf("BodyRoll %.2f|", UnitConverter::radiansToDegrees(vehicle.getBody().getRollAngleRelateChassis()));
}

void VehicleDebuger::paintText(DrivingInputData& inputData) {
    const char* reset = "\033[0m";
    const char* green = "\033[1;32m";
    const char* red = "\033[1;31m";
    if (inputData.getThrottleRatio() > 0.0f) {
        std::cout << green;
    } else if (inputData.getBrakeRatio() > 0.0f) {
        std::cout << red;
    } else {
        std::cout << reset;
    }
}
