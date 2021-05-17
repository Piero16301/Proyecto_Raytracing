#ifndef ADVANCED_RAYTRACER_PLANE_H
#define ADVANCED_RAYTRACER_PLANE_H

#include "Vector3D.h"
#include "Color.h"
#include "Object.h"

class Plane : public Object {
public:
    Vector3D normal;
    double distance;
    Color color;

public:
    Plane();
    Plane(Vector3D normalValue, double distanceValue, Color colorValue);

    Vector3D getPlaneNormal() const;
    double getPlaneDistance() const;
    Color getColor() override;

    Vector3D getNormalAt(Vector3D point) override;
    double findIntersection(Ray ray) override;
};

#endif //ADVANCED_RAYTRACER_PLANE_H
