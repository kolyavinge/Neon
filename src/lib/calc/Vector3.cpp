#include <lib/HashCode.h>
#include <lib/Numeric.h>
#include <lib/calc/Math.h>
#include <lib/calc/Vector3.h>

Vector3::Vector3() {
    set(0.0f, 0.0f, 0.0f);
}

Vector3::Vector3(float valueX, float valueY, float valueZ) {
    set(valueX, valueY, valueZ);
}

void Vector3::set(float valueX, float valueY, float valueZ) {
    x = valueX;
    y = valueY;
    z = valueZ;
}

bool Vector3::isZero(float eps) {
    return
        Numeric::floatEquals(x, 0.0f, eps) &&
        Numeric::floatEquals(y, 0.0f, eps) &&
        Numeric::floatEquals(z, 0.0f, eps);
}

bool Vector3::equals(Object& v) {
    Vector3& other = (Vector3&)v;
    return x == other.x && y == other.y && z == other.z;
}

int Vector3::getHashCode() {
    HashCode hash;
    hash.add(x);
    hash.add(y);
    hash.add(z);
    int code = hash.getResult();

    return code;
}

float Vector3::getLength() {
    return Math::sqrt(x * x + y * y + z * z);
}

float Vector3::getLengthTo(Vector3& v) {
    float dx = x - v.x;
    float dy = y - v.y;
    float dz = z - v.z;

    return Math::sqrt(dx * dx + dy * dy + dz * dz);
}

Vector3 Vector3::getDirectionTo(Vector3 v) {
    v.sub(*this);
    return v;
}

void Vector3::setLength(float newLength) {
    if (newLength < 0.0f) throw InvalidVectorLengthException();
    float currentLength = getLength();
    raiseErrorIfCurrentLengthZero(currentLength);
    mul(newLength / currentLength);
}

void Vector3::add(Vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vector3::addMultiplied(Vector3& v, float multipliedBy) {
    x += multipliedBy * v.x;
    y += multipliedBy * v.y;
    z += multipliedBy * v.z;
}

void Vector3::sub(Vector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void Vector3::mul(float a) {
    x *= a;
    y *= a;
    z *= a;
}

void Vector3::div(float a) {
    x /= a;
    y /= a;
    z /= a;
}

bool Vector3::isCollinear(Vector3& v, float eps) {
    float dot = dotProduct(v);

    return Numeric::floatEquals(dot, 1.0f, eps);
}

float Vector3::dotProduct(Vector3& v) {
    return x * v.x + y * v.y + z * v.z;
}

void Vector3::vectorProduct(Vector3& v) {
    float px = y * v.z - z * v.y;
    float py = z * v.x - x * v.z;
    float pz = x * v.y - y * v.x;
    x = px;
    y = py;
    z = pz;
}

void Vector3::normalize() {
    float currentLength = getLength();
    raiseErrorIfCurrentLengthZero(currentLength);
    x /= currentLength;
    y /= currentLength;
    z /= currentLength;
}

Vector3 Vector3::getNormalized() {
    Vector3 normalized = *this;
    normalized.normalize();

    return normalized;
}

void Vector3::reflectBy(Vector3& normal) {
    // reflected = vector - 2 * (vector * normal) * normal
    float product = 2.0f * dotProduct(normal);
    x -= product * normal.x;
    y -= product * normal.y;
    z -= product * normal.z;
}

void Vector3::raiseErrorIfCurrentLengthZero(float length) {
    if (Numeric::floatEquals(length, 0.0f)) {
        throw InvalidVectorLengthException();
    }
}
