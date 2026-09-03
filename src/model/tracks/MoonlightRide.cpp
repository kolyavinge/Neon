#include <lib/calc/Vector3.h>
#include <model/tracks/MoonlightRide.h>
#include <model/world/GroundBuilder.h>
#include <model/world/RoadBarrierBuilder.h>

MoonlightRide::MoonlightRide() {
    makeGround();
    makeRoadBarriers();
}

String MoonlightRide::getName() {
    return String("Moonlight ride");
}

void MoonlightRide::makeGround() {
    GetZFunc getZFunc = [](Vector3 p, int row, int col, int segmentsCountDownToUp, int segmentsCountLeftToRight) {
        //if (row <= 3) return p.z + 0.01f;
        //return p.z + (float)(col % 2) * 0.1f + (float)(row % 2) * 0.1f + 0.01f;
        return p.z + 0.01f;
    };

    GroundBuilder builder;
    builder.setResultList(_groundPrimitives);

    builder
        .setKind(WorldPrimitiveKind::asphalt1)
        .setBasePlane(Vector3(-10.0f, -10.0f, 0.0f), Vector3(10.0f, -10.0f, 0.0f), Vector3(-10.0f, 10.0f, 0.0f))
        .splitLeftToRight(10)
        .splitDownToUp(10)
        .setZFunc(getZFunc)
        .build();
}

void MoonlightRide::makeRoadBarriers() {
    RoadBarrierBuilder builder;
    builder.setResultList(_barrierPrimitives);

    builder
        .setKind(WorldPrimitiveKind::metalBarrier1)
        .setPosition(Vector3(-2.0f, 2.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), BarrierOrientation::leftBarrier)
        .setCount(5)
        .build();
}
