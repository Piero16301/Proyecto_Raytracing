#ifndef ADVANCED_RAYTRACER_CYLINDER_H
#define ADVANCED_RAYTRACER_CYLINDER_H

#include "Object.h"
#include "Vector3D.h"
#include "Color.h"

class Cylinder : public Object {
public:
    Vector3D center;
    double radius;
    double height;
    Color color;
    int type = 2;

public:
    Cylinder();
    Cylinder(Vector3D centerValue, double radiusValue, double heightValue, Color colorValue);

    Vector3D getCylinderCenter() const;
    double getCylinderRadius() const;
    double getCylinderHeight() const;
    Color getColor() override;

    Vector3D getNormalAt(Vector3D point) override;
    double findIntersection(Ray ray) override;
    int getType() override;
};

#endif //ADVANCED_RAYTRACER_CYLINDER_H
