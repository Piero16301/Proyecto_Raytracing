#include "Vector3D.h"

Vector3D::Vector3D() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3D::Vector3D(double i, double j, double k) {
    x = i;
    y = j;
    z = k;
}

double Vector3D::getVectX() const {
    return x;
}

double Vector3D::getVectY() const {
    return y;
}

double Vector3D::getVectZ() const {
    return z;
}

double Vector3D::magnitude() const {
    return sqrt((x*x) + (y*y) + (z*z));
}

Vector3D Vector3D::normalize() const {
    double magnitude = sqrt((x*x) + (y*y) + (z*z));
    return Vector3D(x/magnitude, y/magnitude, z/magnitude);
}

Vector3D Vector3D::negative() const {
    return Vector3D(-x, -y, -z);
}

double Vector3D::dotProduct(Vector3D v) const {
    return x * v.getVectX() + y * v.getVectY() + z * v.getVectZ();
}

Vector3D Vector3D::crossProduct(Vector3D v) const {
    return Vector3D(y * v.getVectZ() - z * v.getVectY(), z * v.getVectX() - x * v.getVectZ(), x * v.getVectY() - y * v.getVectX());
}

Vector3D Vector3D::vectAdd(Vector3D v) const {
    return Vector3D(x + v.getVectX(), y + v.getVectY(), z + v.getVectZ());
}

Vector3D Vector3D::vectMult(double scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}
