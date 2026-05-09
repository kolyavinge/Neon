#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Geometry {

public:
    static Vector3 rotatePoint(Vector3 point, float angle, Vector3& pivotAxis, Vector3& pivotPoint);
};
