#include <common/constants.h>
#include <lib/calc/Math.h>
#include <lib/calc/Vector3.h>
#include <model/tracks/MoonlightRide.h>
#include <model/world/GroundBuilder.h>
#include <model/world/RoadBarrierBuilder.h>

String MoonlightRide::getName() {
    return String("Moonlight ride");
}

void MoonlightRide::buildInternal() {
    makeGround();
    makeRoadBarriers();
    makeSplitPlanes();
    _globalLight.setPosition(Vector3(0.0f, CommonConstants::maxPerspectiveDepth - 1.0f, CommonConstants::maxPerspectiveDepth - 1.0f));
    float lightValue = 1.5f;
    _globalLight.setColor(Vector3(lightValue, lightValue, lightValue));
    setPlayerPosition();
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
        .splitDownToUp(20)
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
        .splitLeftToRight(40)
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
        .splitLeftToRight(20)
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
        .splitDownToUp(40)
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
        .splitDownToUp(100)
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
        .splitDownToUp(40)
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
    RoadBarrierBuilder leftBarrierBuilder;
    leftBarrierBuilder
        .setResultList(_barrierPrimitives)
        .setGroundPrimitives(_groundPrimitives)
        .setOuterCorners(_outerCorners)
        .setBarrierOrientation(BarrierOrientation::leftBarrier);

    RoadBarrierBuilder rightBarrierBuilder;
    rightBarrierBuilder
        .setResultList(_barrierPrimitives)
        .setGroundPrimitives(_groundPrimitives)
        .setOuterCorners(_outerCorners)
        .setBarrierOrientation(BarrierOrientation::rightBarrier);

    leftBarrierBuilder
        .setKind(WorldPrimitiveKind::metalBarrier1)
        .setPosition(Vector3(2.0f, 0.0f, 0.0f))
        .setDirection(Vector3(0.0f, 1.0f, 0.0f))
        .setCount(50)
        .build()
        .calculateZ()
        .setCount(59)
        .build();

    rightBarrierBuilder
        .setKind(WorldPrimitiveKind::metalBarrier1)
        .setPosition(Vector3(18.0f, 15.0f, 0.0f))
        .setDirection(Vector3(0.0f, 1.0f, 0.0f))
        .setCount(40)
        .build()
        .calculateZ()
        .setCount(53)
        .build();

    // первый поворот

    leftBarrierBuilder
        .rotateDirection(-Math::piQuarter)
        .setCount(1)
        .build()
        .setDirection(Vector3(1.0f, 0.0f, 0.0f))
        .setCount(20)
        .build();

    rightBarrierBuilder
        .rotateDirection(-Math::piQuarter)
        .setCount(1)
        .build()
        .setDirection(Vector3(1.0f, 0.0f, 0.0f))
        .setCount(19)
        .build();

    // второй поворот

    leftBarrierBuilder
        .rotateDirection(Math::piQuarter)
        .setCount(1)
        .build()
        .setDirection(Vector3(0.0f, 1.0f, 0.0f))
        .setCount(21)
        .build()
        .rotateDirection(Math::piQuarter)
        .setCount(1)
        .build()
        .setDirection(Vector3(-1.0f, 0.0f, 0.0f))
        .calculateZ()
        .setCount(21)
        .build()
        .rotateDirection(-Math::piQuarter)
        .setCount(1)
        .build();

    rightBarrierBuilder
        .rotateDirection(Math::piQuarter)
        .setCount(1)
        .build()
        .setDirection(Vector3(0.0f, 1.0f, 0.0f))
        .setCount(37)
        .build()
        .rotateDirection(Math::piQuarter)
        .setCount(1)
        .build()
        .setDirection(Vector3(-1.0f, 0.0f, 0.0f))
        .calculateZ()
        .setCount(19)
        .build()
        .rotateDirection(-Math::piQuarter)
        .setCount(1)
        .build()
        .setDirection(Vector3(0.0f, 1.0f, 0.0f))
        .setCount(2)
        .build()
        .setDirection(Vector3(1.0f, 0.0f, 0.0f))
        .setCount(1)
        .build();

    // длинная прямая

    leftBarrierBuilder
        .setDirection(Vector3(0.0f, 1.0f, 0.0f))
        .setCount(606)
        .build()
        .rotateDirection(-Math::piQuarter)
        .setCount(1)
        .build()
        .setDirection(Vector3(1.0f, 0.0f, 0.0f))
        .setCount(10)
        .build();

    // последний правый барьер образует внешний угол с самым первым правым барьером
    rightBarrierBuilder.addOuterCornerAtLastBarrierPosition();
}

void MoonlightRide::makeSplitPlanes() {
    WorldPrimitiveMinMaxPointFinder finder;
    finder.findMinMaxPointFor(getGroundPrimitives());
    Vector3 min = finder.getMinPoint();
    Vector3 max = finder.getMaxPoint();

    _splitPlanes.addByValue(Plane(Vector3(1.0f, 0.0f, 0.0f), Vector3((min.x + max.x) / 2.0f, 0.0f, 0.0f)));

    auto splitRec = [&](float minY, float maxY, auto&& self) {
        if (maxY - minY <= 10.0f) return;
        float middle = (minY + maxY) / 2.0f;
        _splitPlanes.addByValue(Plane(Vector3(0.0f, 1.0f, 0.0f), Vector3(min.x, middle, 0.0f)));
        _splitPlanes.addByValue(Plane(Vector3(0.0f, 1.0f, 0.0f), Vector3(max.x, middle, 0.0f)));
        self(minY, middle, self);
        self(middle, maxY, self);
    };

    splitRec(min.y, max.y, splitRec);
}

void MoonlightRide::setPlayerPosition() {
    _playerCenter.set(Vector3(10.0f, 10.0f, 1.0f));
    //_playerCenter.set(Vector3(30.0f, 210.0f, 6.0f));
    //_playerCenter.set(Vector3(10.0f, 270.0f, 4.0f));
    //_playerCenter.set(Vector3(10.0f, 1450.0f, 4.0f));

    // на этой позиции неверно работала проверка соударений с землей
    //_playerCenter.set(Vector3(306.0f, 1085.8f, -15.0f));

    //_playerCenter.set(Vector3(306.0f, 1085.8f, -18.0f));

    //_playerRotationAngle = Math::pi;
    _playerRotationAngle = -1.6f;
}
