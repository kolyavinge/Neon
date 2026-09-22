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
    builder
        .setResultList(_groundPrimitives)
        .setDirections(CommonConstants::rightAxis, CommonConstants::frontAxis)
        .setTextureScale(5.0f);

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(0.0f, 0.0f, 0.0f))
        .setSize(20.0f, 100.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(builder.getBasePlaneUpLeft())
        .setSize(20.0f, 100.0f)
        .setSmoothAscendDownToUp(5.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(builder.getBasePlaneUpLeft())
        .setSize(20.0f, 20.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(builder.getBasePlaneDownRight())
        .setSize(40.0f, 20.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneUpRight().x - 20.0f, builder.getBasePlaneUpRight().y, builder.getBasePlaneUpRight().z))
        .setSize(20.0f, 60.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneUpLeft().x - 20.0f, builder.getBasePlaneUpLeft().y - 20.0f, builder.getBasePlaneUpLeft().z - 2.0f))
        .setSize(20.0f, 20.0f)
        .splitLeftToRight(10)
        .setSmoothAscendLeftToRight(2.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneDownLeft().x - 20.0f, builder.getBasePlaneDownLeft().y, builder.getBasePlaneDownLeft().z))
        .setSize(20.0f, 20.0f)
        .build();

    // длинная прямая
    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(builder.getBasePlaneUpLeft())
        .setSize(20.0f, 1200.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneUpRight().x, builder.getBasePlaneUpRight().y - 20.0f, builder.getBasePlaneUpRight().z))
        .setSize(100.0f, 20.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneUpRight().x, builder.getBasePlaneUpRight().y - 60.0f, builder.getBasePlaneUpRight().z))
        .setSize(100.0f, 60.0f)
        .splitLeftToRight(10)
        .setSmoothDescendLeftToRight(3.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(builder.getBasePlaneDownRight())
        .setSize(100.0f, 20.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneDownRight().x - 20.0f, builder.getBasePlaneDownRight().y - 20.0f, builder.getBasePlaneDownRight().z + 3.0f))
        .setSize(20.0f, 20.0f)
        .splitDownToUp(10)
        .setSmoothDescendDownToUp(3.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneDownRight().x - 20.0f, builder.getBasePlaneDownRight().y - 80.0f, builder.getBasePlaneDownRight().z))
        .setSize(20.0f, 80.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneDownRight().x - 20.0f, builder.getBasePlaneDownRight().y - 40.0f, builder.getBasePlaneDownRight().z - 10.0f))
        .setSize(20.0f, 40.0f)
        .splitDownToUp(10)
        .setSmoothAscendDownToUp(10.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneDownRight().x - 20.0f, builder.getBasePlaneDownRight().y - 150.0f, builder.getBasePlaneDownRight().z))
        .setSize(20.0f, 150.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneDownRight().x - 20.0f, builder.getBasePlaneDownRight().y - 50.0f, builder.getBasePlaneDownRight().z - 12.0f))
        .setSize(20.0f, 50.0f)
        .splitDownToUp(10)
        .setSmoothAscendDownToUp(12.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneDownRight().x - 60.0f, builder.getBasePlaneDownRight().y - 800.0f, builder.getBasePlaneDownRight().z + 20.0f))
        .setSize(60.0f, 800.0f)
        .setSmoothDescendDownToUp(20.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneDownLeft().x, builder.getBasePlaneDownLeft().y - 20.0f, builder.getBasePlaneDownLeft().z))
        .setSize(300.0f, 20.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(builder.getBasePlaneDownRight().x - 60.0f, builder.getBasePlaneDownRight().y - 260.0f, builder.getBasePlaneDownRight().z))
        .setSize(60.0f, 260.0f)
        .build();

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlaneDownLeft(Vector3(20.0f, 0.0f, 0.0f))
        .setSize(480.0f, 20.0f)
        .setSmoothAscendLeftToRight(1.0f)
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
    _splitPlanes.addByValue(Plane(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 20.0f, 0.0f)));
    _splitPlanes.addByValue(Plane(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)));
}
