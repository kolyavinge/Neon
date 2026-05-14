#include <lib/calc/Plane.h>

Plane::Plane() {}

Plane::Plane(Vector3 frontNormal, Vector3 basePoint) {
    _frontNormal = frontNormal;
    _basePoint = basePoint;
}

Vector3& Plane::getFrontNormal() {
    return _frontNormal;
}

Vector3& Plane::getBasePoint() {
    return _basePoint;
}

bool Plane::isPointInFront(Vector3& point) {
    return _basePoint.getDirectionTo(point).dotProduct(_frontNormal) >= 0.0f;
}

bool Plane::contains(Vector3& point, float eps) {
    // уравнение плоскости
    float a = _frontNormal.x;
    float b = _frontNormal.y;
    float c = _frontNormal.z;
    float d = -_frontNormal.dotProduct(_basePoint);
    float v = a * point.x + b * point.y + c * point.z + d;
    bool result = Numeric::floatEquals(v, 0.0f, eps);

    return result;
}

bool Plane::hasCollision(Vector3 startPoint, Vector3 endPoint, float eps, output Vector3& collisionPoint) {
    float startPointDotProduct = _basePoint.getDirectionTo(startPoint).dotProduct(_frontNormal);
    float endPointDotProduct = _basePoint.getDirectionTo(endPoint).dotProduct(_frontNormal);

    // чтобы пересечение было, скалярные произведения должны иметь разные знаки
    if (startPointDotProduct * endPointDotProduct > 0.0f) {
        return false;
    }

    Vector3 frontNormal = _frontNormal;
    // для правильной работы алгоритма startPoint должна находится перед лицевой стороной плоскости (dotProduct > 0)
    if (startPointDotProduct < 0.0f) {
        // такая ситуация возможна, если мы находим пересечение с обьектом, представленным в виде пересекающихся плоскостей
        // поворачивам плоскость на 180 градусов
        // (лучше повернуть плоскость, а не менять местами startPoint и endPoint)
        frontNormal.mul(-1.0f);
    }

    // бинарный поиск
    float length = startPoint.getLengthTo(endPoint);
    Vector3 middlePoint = startPoint.getMiddleTo(endPoint);
    while (length > eps) {
        float dotProduct = _basePoint.getDirectionTo(middlePoint).dotProduct(frontNormal);
        if (dotProduct > 0.0f) {
            startPoint = middlePoint;
        } else {
            endPoint = middlePoint;
        }
        length /= 2.0f;
        middlePoint = startPoint.getMiddleTo(endPoint);
    }

    // в качестве окончательной точки пересечения берем startPoint
    // удобно, когда результирующая точка лежит перед лицевой стороной плоскости
    collisionPoint = startPoint;

    return true;
}
