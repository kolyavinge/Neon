#include <lib/Memory.h>
#include <lib/calc/Math.h>
#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>

TransformMatrix4 TransformMatrix4::identity;

TransformMatrix4::TransformMatrix4() {
    setIdentity();
}

TransformMatrix4::TransformMatrix4(float items[16]) {
    Memory::copy<float>(items, _items, 16);
}

TransformMatrix4& TransformMatrix4::operator=(const TransformMatrix4& other) {
    Memory::copy<float>(other._items, _items, 16);
    return *this;
}

float* TransformMatrix4::getItems() {
    return _items;
}

void TransformMatrix4::setIdentity() {
    setZero();
    _items[0] = 1.0f;
    _items[5] = 1.0f;
    _items[10] = 1.0f;
    _items[15] = 1.0f;
}

void TransformMatrix4::setZero() {
    Memory::zero<float>(_items, 16);
}

void TransformMatrix4::mul(TransformMatrix4& m) {
    // col 1
    float item0 = _items[0] * m._items[0] + _items[4] * m._items[1] + _items[8] * m._items[2] + _items[12] * m._items[3];
    float item1 = _items[1] * m._items[0] + _items[5] * m._items[1] + _items[9] * m._items[2] + _items[13] * m._items[3];
    float item2 = _items[2] * m._items[0] + _items[6] * m._items[1] + _items[10] * m._items[2] + _items[14] * m._items[3];
    float item3 = _items[3] * m._items[0] + _items[7] * m._items[1] + _items[11] * m._items[2] + _items[15] * m._items[3];
    // col 2
    float item4 = _items[0] * m._items[4] + _items[4] * m._items[5] + _items[8] * m._items[6] + _items[12] * m._items[7];
    float item5 = _items[1] * m._items[4] + _items[5] * m._items[5] + _items[9] * m._items[6] + _items[13] * m._items[7];
    float item6 = _items[2] * m._items[4] + _items[6] * m._items[5] + _items[10] * m._items[6] + _items[14] * m._items[7];
    float item7 = _items[3] * m._items[4] + _items[7] * m._items[5] + _items[11] * m._items[6] + _items[15] * m._items[7];
    // col 3
    float item8 = _items[0] * m._items[8] + _items[4] * m._items[9] + _items[8] * m._items[10] + _items[12] * m._items[11];
    float item9 = _items[1] * m._items[8] + _items[5] * m._items[9] + _items[9] * m._items[10] + _items[13] * m._items[11];
    float item10 = _items[2] * m._items[8] + _items[6] * m._items[9] + _items[10] * m._items[10] + _items[14] * m._items[11];
    float item11 = _items[3] * m._items[8] + _items[7] * m._items[9] + _items[11] * m._items[10] + _items[15] * m._items[11];
    // col 4
    float item12 = _items[0] * m._items[12] + _items[4] * m._items[13] + _items[8] * m._items[14] + _items[12] * m._items[15];
    float item13 = _items[1] * m._items[12] + _items[5] * m._items[13] + _items[9] * m._items[14] + _items[13] * m._items[15];
    float item14 = _items[2] * m._items[12] + _items[6] * m._items[13] + _items[10] * m._items[14] + _items[14] * m._items[15];
    float item15 = _items[3] * m._items[12] + _items[7] * m._items[13] + _items[11] * m._items[14] + _items[15] * m._items[15];

    _items[0] = item0;
    _items[1] = item1;
    _items[2] = item2;
    _items[3] = item3;
    _items[4] = item4;
    _items[5] = item5;
    _items[6] = item6;
    _items[7] = item7;
    _items[8] = item8;
    _items[9] = item9;
    _items[10] = item10;
    _items[11] = item11;
    _items[12] = item12;
    _items[13] = item13;
    _items[14] = item14;
    _items[15] = item15;
}

Vector4 TransformMatrix4::mul(Vector4 v) {
    float x = _items[0] * v.x + _items[4] * v.y + _items[8] * v.z + _items[12] * v.w;
    float y = _items[1] * v.x + _items[5] * v.y + _items[9] * v.z + _items[13] * v.w;
    float z = _items[2] * v.x + _items[6] * v.y + _items[10] * v.z + _items[14] * v.w;
    float w = _items[3] * v.x + _items[7] * v.y + _items[11] * v.z + _items[15] * v.w;

    return Vector4(x, y, z, w);
}

Vector3 TransformMatrix4::mul(Vector3 v, float valueW) {
    float x = _items[0] * v.x + _items[4] * v.y + _items[8] * v.z + _items[12] * valueW;
    float y = _items[1] * v.x + _items[5] * v.y + _items[9] * v.z + _items[13] * valueW;
    float z = _items[2] * v.x + _items[6] * v.y + _items[10] * v.z + _items[14] * valueW;

    return Vector3(x, y, z);
}

void TransformMatrix4::transpose() {
    float i0 = _items[0];
    float i1 = _items[1];
    float i2 = _items[2];
    float i3 = _items[3];
    float i4 = _items[4];
    float i5 = _items[5];
    float i6 = _items[6];
    float i7 = _items[7];
    float i8 = _items[8];
    float i9 = _items[9];
    float i10 = _items[10];
    float i11 = _items[11];
    float i12 = _items[12];
    float i13 = _items[13];
    float i14 = _items[14];
    float i15 = _items[15];

    float transposed[16] = {
        i0, i1, i2, i3,
        i4, i5, i6, i7,
        i8, i9, i10, i11,
        i12, i13, i14, i15
    };

    Memory::copy(transposed, _items, 16);
}

void TransformMatrix4::translate(float x, float y, float z) {
    setIdentity();
    _items[12] = x;
    _items[13] = y;
    _items[14] = z;
}

void TransformMatrix4::translate(Vector3& v) {
    translate(v.x, v.y, v.z);
}

void TransformMatrix4::rotate(float angle, float axisX, float axisY, float axisZ) {
    float sin = Math::sin(angle);
    float cos = Math::cos(angle);
    float oneMinusCos = 1.0f - cos;
    // col 1
    _items[0] = cos + axisX * axisX * oneMinusCos;
    _items[1] = axisY * axisX * oneMinusCos + axisZ * sin;
    _items[2] = axisZ * axisX * oneMinusCos - axisY * sin;
    _items[3] = 0.0f;
    // col 2
    _items[4] = axisX * axisY * oneMinusCos - axisZ * sin;
    _items[5] = cos + axisY * axisY * oneMinusCos;
    _items[6] = axisZ * axisY * oneMinusCos + axisX * sin;
    _items[7] = 0.0f;
    // col 3
    _items[8] = axisX * axisZ * oneMinusCos + axisY * sin;
    _items[9] = axisY * axisZ * oneMinusCos - axisX * sin;
    _items[10] = cos + axisZ * axisZ * oneMinusCos;
    _items[11] = 0.0f;
    // col 4
    _items[12] = 0.0f;
    _items[13] = 0.0f;
    _items[14] = 0.0f;
    _items[15] = 1.0f;
}

void TransformMatrix4::rotate(float angle, Vector3& axis) {
    rotate(angle, axis.x, axis.y, axis.z);
}

void TransformMatrix4::scale(float x, float y, float z) {
    setZero();
    _items[0] = x;
    _items[5] = y;
    _items[10] = z;
    _items[15] = 1.0f;
}

void TransformMatrix4::lookAt(
    float eyeX, float eyeY, float eyeZ,
    float lookDirectionX, float lookDirectionY, float lookDirectionZ,
    float upX, float upY, float upZ) {
    Vector3 eye, lookDirection, up;
    eye.set(eyeX, eyeY, eyeZ);
    lookDirection.set(lookDirectionX, lookDirectionY, lookDirectionZ);
    up.set(upX, upY, upZ);
    Vector3 s = lookDirection;
    s.vectorProduct(up);
    s.normalize();
    Vector3 u = s;
    u.vectorProduct(lookDirection);
    // col 1
    _items[0] = s.x;
    _items[1] = u.x;
    _items[2] = -lookDirectionX;
    _items[3] = 0.0f;
    // col 2
    _items[4] = s.y;
    _items[5] = u.y;
    _items[6] = -lookDirectionY;
    _items[7] = 0.0f;
    // col 3
    _items[8] = s.z;
    _items[9] = u.z;
    _items[10] = -lookDirectionZ;
    _items[11] = 0.0f;
    // col 4
    _items[12] = -eye.dotProduct(s);
    _items[13] = -eye.dotProduct(u);
    _items[14] = eye.dotProduct(lookDirection);
    _items[15] = 1.0f;
}

void TransformMatrix4::lookAt(Vector3& eyePosition, Vector3& lookDirection, Vector3& upDirection) {
    lookAt(
        eyePosition.x, eyePosition.y, eyePosition.z,
        lookDirection.x, lookDirection.y, lookDirection.z,
        upDirection.x, upDirection.y, upDirection.z);
}

void TransformMatrix4::ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
    // col 1
    _items[0] = 2.0f / (right - left);
    _items[1] = 0.0f;
    _items[2] = 0.0f;
    _items[3] = 0.0f;
    // col 2
    _items[4] = 0.0f;
    _items[5] = 2.0f / (top - bottom);
    _items[6] = 0.0f;
    _items[7] = 0.0f;
    // col 3
    _items[8] = 0.0f;
    _items[9] = 0.0f;
    _items[10] = -2.0f / (zFar - zNear);
    _items[11] = 0.0f;
    // col 4
    _items[12] = -(right + left) / (right - left);
    _items[13] = -(top + bottom) / (top - bottom);
    _items[14] = -(zFar + zNear) / (zFar - zNear);
    _items[15] = 1.0f;
}

void TransformMatrix4::perspective(float viewAngle, float screenAspect, float zNear, float zFar) {
    float f = 1.0f / Math::tan(viewAngle / 2.0f);
    // col 1
    _items[0] = f / screenAspect;
    _items[1] = 0.0f;
    _items[2] = 0.0f;
    _items[3] = 0.0f;
    // col 2
    _items[4] = 0.0f;
    _items[5] = f;
    _items[6] = 0.0f;
    _items[7] = 0.0f;
    // col 3
    _items[8] = 0.0f;
    _items[9] = 0.0f;
    _items[10] = (zFar + zNear) / (zNear - zFar);
    _items[11] = -1.0f;
    // col 4
    _items[12] = 0.0f;
    _items[13] = 0.0f;
    _items[14] = (2.0f * zFar * zNear) / (zNear - zFar);
    _items[15] = 0.0f;
}
