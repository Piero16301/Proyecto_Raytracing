#ifndef ADVANCED_RAYTRACER_RAY_H
#define ADVANCED_RAYTRACER_RAY_H

#include "Vector3D.h"

class Ray {
public:
    Vector3D origin, direction;

public:
    Ray();
    Ray(Vector3D o, Vector3D d);

    Vector3D getRayOrigin() const;
    Vector3D getRayDirection() const;
};

#endif //ADVANCED_RAYTRACER_RAY_H
