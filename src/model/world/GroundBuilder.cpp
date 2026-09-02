#include <model/world/GroundBuilder.h>

GroundBuilder::GroundBuilder() {
    init();
}

void GroundBuilder::init() {
    _segmentsCountLeftToRight = 1;
    _segmentsCountDownToUp = 1;
    _getZFunc = nullptr;
}

GroundBuilder& GroundBuilder::setBasePlane(Vector3 downLeft, Vector3 downRight, Vector3 upLeft) {
    init();
    _basePlaneDownLeft = downLeft;
    _basePlaneDownRight = downRight;
    _basePlaneUpLeft = upLeft;
    _resultPrimitives.clear();

    return *this;
}

GroundBuilder& GroundBuilder::splitLeftToRight(int segmentsCount) {
    if (segmentsCount <= 0) throw ArgumentException();
    _segmentsCountLeftToRight = segmentsCount;

    return *this;
}

GroundBuilder& GroundBuilder::splitDownToUp(int segmentsCount) {
    if (segmentsCount <= 0) throw ArgumentException();
    _segmentsCountDownToUp = segmentsCount;

    return *this;
}

GroundBuilder& GroundBuilder::setZFunc(GetZFunc getZ) {
    if (getZ == nullptr) throw ArgumentException();
    _getZFunc = getZ;

    return *this;
}

GroundBuilder& GroundBuilder::build() {
    Vector3 right = _basePlaneDownLeft.getDirectionTo(_basePlaneDownRight);
    Vector3 up = _basePlaneDownLeft.getDirectionTo(_basePlaneUpLeft);
    Vector3 basePlaneFrontNormal = right;
    basePlaneFrontNormal.crossProduct(up);
    basePlaneFrontNormal.normalize();
    Vector3 basePlaneUpRight = _basePlaneUpLeft;
    basePlaneUpRight.add(right);
    Vector3 rightStep = right;
    Vector3 upStep = up;
    rightStep.div((float)_segmentsCountLeftToRight);
    upStep.div((float)_segmentsCountDownToUp);

    auto getBasePlanePoint = [&](int row, int col) {
        Vector3 result;
        if (row == 0 && col == 0) result = _basePlaneDownLeft;
        else if (row == 0 && col == _segmentsCountLeftToRight) result = _basePlaneDownRight;
        else if (row == _segmentsCountDownToUp && col == 0) result = _basePlaneUpLeft;
        else if (row == _segmentsCountDownToUp && col == _segmentsCountLeftToRight) result = basePlaneUpRight;
        else {
            result = _basePlaneDownLeft;
            result.addMultiplied(rightStep, (float)col);
            result.addMultiplied(upStep, (float)row);
        }
        if (_getZFunc != nullptr) {
            result.z = _getZFunc(result, row, col, _segmentsCountDownToUp, _segmentsCountLeftToRight);
        }

        return result;
    };

    for (int row = 0; row < _segmentsCountDownToUp; row++) {
        for (int col = 0; col < _segmentsCountLeftToRight; col++) {
            Vector3 p1 = getBasePlanePoint(row, col);
            Vector3 p2 = getBasePlanePoint(row, col + 1);
            Vector3 p3 = getBasePlanePoint(row + 1, col + 1);
            Vector3 p4 = getBasePlanePoint(row + 1, col);
            _resultPrimitives.addByValue(WorldPrimitive(p1, p2, p3, p4));
        }
    }

    return *this;
}

Collection<WorldPrimitive>& GroundBuilder::getResultPrimitives() {
    return _resultPrimitives;
}
