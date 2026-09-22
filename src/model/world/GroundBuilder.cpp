#include <lib/calc/Math.h>
#include <lib/calc/Vector2.h>
#include <model/world/GroundBuilder.h>

GetZFuncData::GetZFuncData() {
    row = 0;
    col = 0;
    segmentsCountDownToUp = 0;
    segmentsCountLeftToRight = 0;
}

GroundBuilder::GroundBuilder() {
    _kind = (WorldPrimitiveKind)-1;
    _resultPrimitives = nullptr;
    init();
}

void GroundBuilder::init() {
    _segmentsCountLeftToRight = 1;
    _segmentsCountDownToUp = 1;
    _getZFunc = nullptr;
}

GroundBuilder& GroundBuilder::setResultList(List<WorldPrimitive>& resultPrimitives) {
    _resultPrimitives = &resultPrimitives;
    return *this;
}

GroundBuilder& GroundBuilder::setTextureScale(float textureScale) {
    if (Numeric::floatEquals(textureScale, 0.0f)) throw ArgumentException();
    _textureScale = textureScale;
    return *this;
}

GroundBuilder& GroundBuilder::setKind(WorldPrimitiveKind kind) {
    _kind = kind;
    return *this;
}

GroundBuilder& GroundBuilder::setBasePlane(Vector3 downLeft, Vector3 downRight, Vector3 upLeft) {
    _basePlaneDownLeft = downLeft;
    _basePlaneDownRight = downRight;
    _basePlaneUpLeft = upLeft;

    return *this;
}

GroundBuilder& GroundBuilder::setBasePlaneDownLeft(Vector3 downLeft) {
    _basePlaneDownLeft = downLeft;

    return *this;
}

GroundBuilder& GroundBuilder::setDirections(Vector3 right, Vector3 front) {
    _rightDirection = right;
    _frontDirection = front;

    return *this;
}

GroundBuilder& GroundBuilder::setSize(float width, float height) {
    _basePlaneDownRight = _basePlaneDownLeft;
    _basePlaneDownRight.addMultiplied(_rightDirection, width);

    _basePlaneUpLeft = _basePlaneDownLeft;
    _basePlaneUpLeft.addMultiplied(_frontDirection, height);

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

GroundBuilder& GroundBuilder::setSmoothAscendDownToUp(float ascend) {
    _basePlaneUpLeft.z += ascend;

    // плавное изменение z с помощью синуса
    // синус нормализован [0;1] и умножен на величину подьема
    _getZFunc = [](GetZFuncData& data) {
        float ascend = data.basePlaneDownLeft.getDirectionTo(data.basePlaneUpLeft).z;
        float x = ((float)data.row / (float)data.segmentsCountDownToUp) * Math::pi - Math::piHalf; // [-pi/2; +pi/2]
        return data.basePlaneDownLeft.z + ascend * Math::sinNormalized(x);
    };

    return *this;
}

GroundBuilder& GroundBuilder::setSmoothAscendLeftToRight(float ascend) {
    _basePlaneDownRight.z += ascend;

    _getZFunc = [](GetZFuncData& data) {
        float ascend = data.basePlaneDownLeft.getDirectionTo(data.basePlaneDownRight).z;
        float x = ((float)data.col / (float)data.segmentsCountLeftToRight) * Math::pi - Math::piHalf;
        return data.basePlaneDownLeft.z + ascend * Math::sinNormalized(x);
    };

    return *this;
}

GroundBuilder& GroundBuilder::setSmoothDescendDownToUp(float descend) {
    return setSmoothAscendDownToUp(-descend);
}

GroundBuilder& GroundBuilder::setSmoothDescendLeftToRight(float descend) {
    return setSmoothAscendLeftToRight(-descend);
}

void GroundBuilder::build() {
    Vector3 right = _basePlaneDownLeft.getDirectionTo(_basePlaneDownRight);
    Vector3 up = _basePlaneDownLeft.getDirectionTo(_basePlaneUpLeft);
    Vector3 basePlaneFrontNormal = right;
    basePlaneFrontNormal.crossProduct(up);
    basePlaneFrontNormal.normalize();
    _basePlaneUpRight = _basePlaneUpLeft;
    _basePlaneUpRight.add(right);
    Vector3 rightStep = right;
    Vector3 upStep = up;

    if (_textureScale > 0.0f) {
        if (_segmentsCountLeftToRight == 1) _segmentsCountLeftToRight = (int)(right.getLength() / _textureScale);
        if (_segmentsCountDownToUp == 1) _segmentsCountDownToUp = (int)(up.getLength() / _textureScale);
    }

    rightStep.div((float)_segmentsCountLeftToRight);
    upStep.div((float)_segmentsCountDownToUp);

    GetZFuncData data;
    data.basePlaneDownLeft = _basePlaneDownLeft;
    data.basePlaneDownRight = _basePlaneDownRight;
    data.basePlaneUpLeft = _basePlaneUpLeft;
    data.basePlaneUpRight = _basePlaneUpRight;
    data.segmentsCountDownToUp = _segmentsCountDownToUp;
    data.segmentsCountLeftToRight = _segmentsCountLeftToRight;

    auto getBasePlanePoint = [&](int row, int col) {
        Vector3 resultPoint;
        if (row == 0 && col == 0) resultPoint = _basePlaneDownLeft;
        else if (row == 0 && col == _segmentsCountLeftToRight) resultPoint = _basePlaneDownRight;
        else if (row == _segmentsCountDownToUp && col == 0) resultPoint = _basePlaneUpLeft;
        else if (row == _segmentsCountDownToUp && col == _segmentsCountLeftToRight) resultPoint = _basePlaneUpRight;
        else {
            resultPoint = _basePlaneDownLeft;
            resultPoint.addMultiplied(rightStep, (float)col);
            resultPoint.addMultiplied(upStep, (float)row);
        }
        if (_getZFunc != nullptr) {
            data.point = resultPoint;
            data.row = row;
            data.col = col;
            resultPoint.z = _getZFunc(data);
        }

        return resultPoint;
    };

    auto getTexCoord = [&](Vector3 p1, Vector3 p2, Vector3 p4, output Vector2& tc1, output Vector2& tc2, output Vector2& tc3, output Vector2& tc4) {
        float stepX = p1.getLengthTo(p2) / _textureScale;
        float stepY = p1.getLengthTo(p4) / _textureScale;
        Vector3 d = _basePlaneDownLeft.getDirectionTo(p1);
        float x = Math::mod(d.x, _textureScale) / _textureScale;
        float y = Math::mod(d.y, _textureScale) / _textureScale;
        tc1.set(x, y);
        tc2.set(x + stepX, y);
        tc3.set(x + stepX, y + stepY);
        tc4.set(x, y + stepY);
    };

    _resultPrimitives->prepareEnoughCapacity(_resultPrimitives->getCount() + _segmentsCountDownToUp * _segmentsCountLeftToRight);
    for (int row = 0; row < _segmentsCountDownToUp; row++) {
        for (int col = 0; col < _segmentsCountLeftToRight; col++) {
            Vector3 p1 = getBasePlanePoint(row, col);
            Vector3 p2 = getBasePlanePoint(row, col + 1);
            Vector3 p3 = getBasePlanePoint(row + 1, col + 1);
            Vector3 p4 = getBasePlanePoint(row + 1, col);
            Vector2 tc1, tc2, tc3, tc4;
            getTexCoord(p1, p2, p4, output tc1, output tc2, output tc3, output tc4);
            _resultPrimitives->addByValue(WorldPrimitive(_kind, p1, p2, p3, p4, tc1, tc2, tc3, tc4));
        }
    }

    init();
}

Vector3 GroundBuilder::getBasePlaneDownLeft() {
    return _basePlaneDownLeft;
}

Vector3 GroundBuilder::getBasePlaneDownRight() {
    return _basePlaneDownRight;
}

Vector3 GroundBuilder::getBasePlaneUpLeft() {
    return _basePlaneUpLeft;
}

Vector3 GroundBuilder::getBasePlaneUpRight() {
    return _basePlaneUpRight;
}
