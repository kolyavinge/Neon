#include <lib/calc/Geometry.h>
#include <lib/calc/Math.h>
#include <lib/calc/Quaternion.h>

Vector3 Geometry::rotatePoint(Vector3 point, float angle, Vector3& pivotAxis, Vector3& pivotPoint) {
    point.sub(pivotPoint);

    // Формула Родрига
    // cos * point + (pivotAxis, point) * (1 - cos) * pivotAxis + sin * [pivotAxis, point]
    // a + b + c

    float sin = Math::sin(angle);
    float cos = Math::cos(angle);

    Vector3 a(point);
    a.mul(cos);

    Vector3 b(pivotAxis);
    b.mul(pivotAxis.dotProduct(point));
    b.mul(1.0f - cos);

    Vector3 c(pivotAxis);
    c.vectorProduct(point);
    c.mul(sin);

    a.add(b);
    a.add(c);

    // Формула Родрига

    a.add(pivotPoint);

    return a;
}

void Geometry::rotateCoordinateSystem(Vector3& axis1From, Vector3& axis1To, Vector3& axis2From, Vector3& axis2To, output float& angle, output Vector3& pivot) {
    Quaternion q1(axis1From, axis1To);
    Vector3 axis2FromRotated(axis2From);
    q1.rotatePoint(axis2FromRotated);
    Quaternion q2(axis2FromRotated, axis2To);
    q2.mul(q1);
    q2.getAngleAndPivot(angle, pivot);
}
