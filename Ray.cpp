#include "Ray.h"

Ray::Ray() {
    origin = Vector3D(0,0,0);
    direction = Vector3D(1,0,0);
}

Ray::Ray(Vector3D o, Vector3D d) {
    origin = o;
    direction = d;
}

Vector3D Ray::getRayOrigin() const {
    return origin;
}

Vector3D Ray::getRayDirection() const {
    return direction;
}
