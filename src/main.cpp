#include <anx/constants.h>
#include <conio.h>
#include <core/di/MainDependencyContainer.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <iomanip>
#include <iostream>
#include <lib/calc/UnitConverter.h>
#include <lib/system.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/Wheel.h>

void showStat(int timeSec, Vehicle& vehicle) {
    Engine& engine = vehicle.getEngine();
    Wheel& wheel = vehicle.getDriveWheel(0);
    Gearbox& gearbox = vehicle.getGearbox();
    std::cout
        << std::fixed << std::setprecision(0)
        << timeSec << "\t"
        << engine.getRpm() << "\t\t"
        << UnitConverter::angularVelocityToRpm(wheel.getAngularVelocity()) * gearbox.getGearRatio() << "\t\t"
        << engine.getTorque() << "\t\t"
        << UnitConverter::msToKmh((wheel.getAngularVelocity() * wheel.getData().radius)) << "\t\t"
        << std::setprecision(4)
        << wheel.getSlipRatio() << "\t\t"
        << std::setprecision(0)
        << UnitConverter::msToKmh(vehicle.getLinearVelocity().getLength()) /*<< " / " << vehicle.getVelocity()*/ << "\t\t"
        << wheel.getTotalPath().getLength()
        << "\r\n";
}

int main() {
    MainDependencyContainer container;
    VehicleUpdater& vehicleUpdater = container.resolve<VehicleUpdater>();
    Vehicle vehicle;
    Engine& engine = vehicle.getEngine();
    Gearbox& gearbox = vehicle.getGearbox();

    std::cout << engine.getEngineStat().getCharBuf() << "\r\n\r\n";

    gearbox.shiftUp();
    //gearbox.shiftUp();
    //gearbox.shiftUp();
    //gearbox.shiftUp();
    //gearbox.shiftUp();
    //gearbox.shiftUp();

    std::cout << "\t" << "Rpm engine\t" << "Rpm wheel+gear\t" << "Torque engine\t" << "Kmh wheel\t" << "Slip ratio\t" << "Kmh\t" << "Travelled meters\t" << "\r\n\r\n";
    std::cout << "\tGear: " << (int)gearbox.getGear() << "\r\n\r\n";
    showStat(0, vehicle);
    int timeSec;
    for (timeSec = 1; timeSec <= 20; timeSec++) {
        for (int frame = 0; frame < (int)CommonConstants::frameRate; frame++) {
            vehicleUpdater.updateVehicle(vehicle);
        }
        showStat(timeSec, vehicle);
    }

    for (; timeSec < 1000; timeSec++) {
        for (int frame = 0; frame < (int)CommonConstants::frameRate; frame++) {
            vehicleUpdater.updateVehicle(vehicle);
        }
    }
    showStat(timeSec, vehicle);

    //system("cls");
    _getch();

    return 0;
}
