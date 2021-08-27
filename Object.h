#ifndef ADVANCED_RAYTRACER_OBJECT_H
#define ADVANCED_RAYTRACER_OBJECT_H

#include "Ray.h"
#include "Vector3D.h"
#include "Color.h"

class Object {
public:
    Object() = default;

    virtual Color getColor();
    virtual Vector3D getNormalAt(Vector3D point);
    virtual double findIntersection(Ray ray);
};

#endif //ADVANCED_RAYTRACER_OBJECT_H
