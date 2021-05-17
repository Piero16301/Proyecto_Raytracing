#ifndef ADVANCED_RAYTRACER_VECTOR3D_H
#define ADVANCED_RAYTRACER_VECTOR3D_H

#include <cmath>

class Vector3D {
public:
    double x{};
    double y{};
    double z{};

public:
    Vector3D();
    Vector3D(double i, double j, double k);

    double getVectX() const;
    double getVectY() const;
    double getVectZ() const;

    double magnitude() const;
    Vector3D normalize() const;
    Vector3D negative() const;
    double dotProduct(Vector3D v) const;
    Vector3D crossProduct(Vector3D v) const;
    Vector3D vectAdd(Vector3D v) const;
    Vector3D vectMult(double scalar) const;
};

#endif //ADVANCED_RAYTRACER_VECTOR3D_H
