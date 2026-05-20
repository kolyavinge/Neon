#include <common/constants.h>
#include <conio.h>
#include <core/di/MainDependencyContainer.h>
#include <debug/stat.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <iomanip>
#include <iostream>
#include <lib/calc/UnitConverter.h>
#include <lib/system.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/Wheel.h>
#include <model/vehicle/DrivingInputData.h>

void showStat(int timeSec, Vehicle& vehicle) {
    Engine& engine = vehicle.getEngine();
    Wheel& wheel = vehicle.getDriveWheel(0);
    Gearbox& gearbox = vehicle.getGearbox();
    std::cout
        << std::fixed << std::setprecision(0)
        << timeSec << "\t"
        << engine.getRpm() << "\t\t"
        << UnitConverter::angularVelocityToRpm(wheel.getAngularVelocity()) * gearbox.getCurrentGearRatio() << "\t\t"
        << UnitConverter::angularVelocityToRpm(wheel.getAngularVelocity()) << "\t\t"
        << engine.getTorque() << "\t\t"
        << std::setprecision(2)
        << wheel.getSlipRatio().value << "\t\t"
        << std::setprecision(0)
        << (vehicle.getLinearVelocity().x < 0 ? "-" : "") << UnitConverter::msToKmh(vehicle.getLinearVelocity().getLength()) << "\t"
        << "\r\n";
}

void showDebugInfo() {
    MainDependencyContainer container;
    VehicleUpdater& vehicleUpdater = container.resolve<VehicleUpdater>();
    VehiclesArray vehicles;
    Vehicle& vehicle = vehicles[0];
    vehicle.init();
    Gearbox& gearbox = vehicle.getGearbox();
    DrivingInputData inputData;

    //std::cout << engine.getEngineStat().getCharBuf() << "\r\n\r\n";

    std::cout << "\t" << "Rpm engine\t" << "Rpm wheel+gear\t" << "Rpm wheel\t" << "Torque engine\t" << "Slip ratio\t" << "Kmh\t" << "\r\n\r\n";

    gearbox.shiftUp();
    std::cout << "\tGear: " << (int)gearbox.getCurrentGear() << "\r\n\r\n";
    int timeSec;
    for (timeSec = 1; timeSec <= 10; timeSec++) {
        for (int frame = 0; frame < (int)CommonConstants::frameRate; frame++) {
            vehicleUpdater.updateVehicles(vehicles, inputData);
        }
        showStat(timeSec, vehicle);
    }
    for (; timeSec < 1000; timeSec++) {
        for (int frame = 0; frame < (int)CommonConstants::frameRate; frame++) {
            vehicleUpdater.updateVehicles(vehicles, inputData);
        }
    }
    showStat(timeSec, vehicle);

    std::cout << "\r\n\r\n";

    vehicle.init();
    gearbox.shiftUp();
    gearbox.shiftUp();
    std::cout << "\tGear: " << (int)gearbox.getCurrentGear() << "\r\n\r\n";
    showStat(0, vehicle);
    for (timeSec = 1; timeSec <= 10; timeSec++) {
        for (int frame = 0; frame < (int)CommonConstants::frameRate; frame++) {
            vehicleUpdater.updateVehicles(vehicles, inputData);
        }
        showStat(timeSec, vehicle);
    }
    for (; timeSec < 1000; timeSec++) {
        for (int frame = 0; frame < (int)CommonConstants::frameRate; frame++) {
            vehicleUpdater.updateVehicles(vehicles, inputData);
        }
    }
    showStat(timeSec, vehicle);

    std::cout << "\r\n\r\n";

    vehicle.init();
    gearbox.shiftUp();
    gearbox.shiftUp();
    gearbox.shiftUp();
    std::cout << "\tGear: " << (int)gearbox.getCurrentGear() << "\r\n\r\n";
    showStat(0, vehicle);
    for (timeSec = 1; timeSec <= 10; timeSec++) {
        for (int frame = 0; frame < (int)CommonConstants::frameRate; frame++) {
            vehicleUpdater.updateVehicles(vehicles, inputData);
        }
        showStat(timeSec, vehicle);
    }
    for (; timeSec < 1000; timeSec++) {
        for (int frame = 0; frame < (int)CommonConstants::frameRate; frame++) {
            vehicleUpdater.updateVehicles(vehicles, inputData);
        }
    }
    showStat(timeSec, vehicle);

    _getch();
}
