#ifndef ADVANCED_RAYTRACER_SPHERE_H
#define ADVANCED_RAYTRACER_SPHERE_H

#include <cmath>

#include "Object.h"
#include "Vector3D.h"
#include "Color.h"

class Sphere : public Object {
public:
    Vector3D center;
    double radius;
    Color color;

public:
    Sphere();
    Sphere(Vector3D centerValue, double radiusValue, Color colorValue);

    Vector3D getSphereCenter() const;
    double getSphereRadius() const;
    Color getColor() override;

    Vector3D getNormalAt(Vector3D point) override;
    double findIntersection(Ray ray) override;
};

#endif //ADVANCED_RAYTRACER_SPHERE_H
