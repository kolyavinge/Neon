#include <common/constants.h>
#include <lib/calc/Vector3.h>
#include <model/tracks/MoonlightRide.h>
#include <model/world/GroundBuilder.h>
#include <model/world/RoadBarrierBuilder.h>

String MoonlightRide::getName() {
    return String("Moonlight ride");
}

void MoonlightRide::buildInternal() {
    makeGround();
    //makeRoadBarriers();
    makeSplitPlanes();
}

void MoonlightRide::makeGround() {
    GroundBuilder builder;
    builder.setResultList(_groundPrimitives);

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(0.0f, 0.0f, 0.0f))
        .setDirections(CommonConstants::rightAxis, CommonConstants::frontAxis)
        .setSize(10.0f, 100.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt2)
        .setBasePlaneDownLeft(builder.getBasePlaneUpLeft())
        .setDirections(CommonConstants::rightAxis, CommonConstants::frontAxis)
        .setSize(10.0f, 100.0f)
        .splitDownToUp(10)
        .setSmoothAscendDownToUp(5.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(builder.getBasePlaneUpLeft())
        .setDirections(CommonConstants::rightAxis, CommonConstants::frontAxis)
        .setSize(10.0f, 20.0f)
        .build();
}

void MoonlightRide::makeRoadBarriers() {
    RoadBarrierBuilder builder;
    builder.setResultList(_barrierPrimitives);

    builder
        .setKind(WorldPrimitiveKind::metalBarrier1)
        .setPosition(Vector3(-2.0f, 10.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), BarrierOrientation::leftBarrier)
        .setCount(5)
        .build();

    builder
        .setKind(WorldPrimitiveKind::metalBarrier1)
        .setPosition(Vector3(-2.0f, 5.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), BarrierOrientation::leftBarrier)
        .setCount(5)
        .build();
}

void MoonlightRide::makeSplitPlanes() {
    _splitPlanes.addByValue(Plane(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f)));
    _splitPlanes.addByValue(Plane(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)));
    _splitPlanes.addByValue(Plane(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)));
}
