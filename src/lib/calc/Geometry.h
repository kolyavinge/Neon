#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Geometry {

public:
    static Vector3 rotatePoint(Vector3 point, float angle, Vector3& pivotAxis, Vector3& pivotPoint);
    static void rotateCoordinateSystem(Vector3& axis1From, Vector3& axis1To, Vector3& axis2From, Vector3& axis2To, output float& angle, output Vector3& pivot);
};
