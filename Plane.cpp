#include "Plane.h"

Plane::Plane() {
    normal = Vector3D(1,0,0);
    distance = 0;
    color = Color(0.5,0.5,0.5,0);
}

Plane::Plane(Vector3D normalValue, double distanceValue, Color colorValue) {
    normal = normalValue;
    distance = distanceValue;
    color = colorValue;
}

Vector3D Plane::getPlaneNormal() const {
    return normal;
}

double Plane::getPlaneDistance() const {
    return distance;
}

Color Plane::getColor() {
    return color;
}

Vector3D Plane::getNormalAt(Vector3D point) {
    return normal;
}

double Plane::findIntersection(Ray ray) {
    Vector3D ray_direction = ray.getRayDirection();

    double a = ray_direction.dotProduct(normal);

    if (a == 0) {
        // Ray paralel to the plane
        return -1;
    } else {
        double b = normal.dotProduct(ray.getRayOrigin().vectAdd(normal.vectMult(distance).negative()));
        return -1 * b / a;
    }
}

int Plane::getType() {
    return type;
}
