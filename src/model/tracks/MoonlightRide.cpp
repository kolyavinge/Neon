#include <lib/calc/Vector3.h>
#include <model/tracks/MoonlightRide.h>
#include <model/world/GroundBuilder.h>

MoonlightRide::MoonlightRide() {
    makeGround();
}

String MoonlightRide::getName() {
    return String("Moonlight ride");
}

void MoonlightRide::makeGround() {
    GetZFunc getZFunc = [](Vector3 p, int row, int col, int segmentsCountDownToUp, int segmentsCountLeftToRight) {
        return p.z + (float)col * 0.0f + (float)row * 0.5f + 0.01f;
    };
    GroundBuilder builder;
    builder
        .setBasePlane(Vector3(-10.0f, 10.0f, 0.0f), Vector3(10.0f, 10.0f, 0.0f), Vector3(-10.0f, 20.0f, 0.0f))
        .splitLeftToRight(10)
        .splitDownToUp(3)
        .setZFunc(getZFunc)
        .build();

    addGroundElements(builder.getResultElements());
}
