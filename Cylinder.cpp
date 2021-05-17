#include <algorithm>

#include "Cylinder.h"

Cylinder::Cylinder() {
    center = Vector3D(0,0,0);
    radius = 1.0;
    height = 1.0;
    color = Color(0.5,0.5,0.5,0,0);
}

Cylinder::Cylinder(Vector3D centerValue, double radiusValue, double heightValue, Color colorValue) {
    center = centerValue;
    radius = radiusValue;
    height = heightValue;
    color = colorValue;
}

Vector3D Cylinder::getCylinderCenter() const {
    return center;
}

double Cylinder::getCylinderRadius() const {
    return radius;
}

double Cylinder::getCylinderHeight() const {
    return height;
}

Color Cylinder::getColor() {
    return color;
}

Vector3D Cylinder::getNormalAt(Vector3D point) {
    Vector3D normal_Vect(point.getVectX() - center.getVectX(), 0, point.getVectZ() - center.getVectZ());
    return normal_Vect.normalize();
}

double Cylinder::findIntersection(Ray ray) {
    double a = (ray.direction.getVectX() * ray.direction.getVectX()) + (ray.direction.getVectZ() * ray.direction.getVectZ());
    double b = 2 * (ray.direction.getVectX() * (ray.origin.getVectX() - center.getVectX()) + ray.direction.getVectZ() * (ray.origin.getVectZ() - center.getVectZ()));
    double c = (ray.origin.getVectX() - center.getVectX()) * (ray.origin.getVectX() - center.getVectX()) + (ray.origin.getVectZ() - center.getVectZ()) * (ray.origin.getVectZ() - center.getVectZ()) - (radius * radius);

    double delta = b * b - 4 * (a * c);
    if (fabs(delta) < 0.000001) {
        return -1;
    }
    if (delta < 0) {
        return -1;
    }

    double t1 = (-b - sqrt(delta)) / (2 * a) - 0.000001;
    double t2 = (-b + sqrt(delta)) / (2 * a) - 0.000001;

    double tValue = std::min(t1, t2);

    double r = ray.origin.getVectY() + tValue * ray.direction.getVectY();
    
    if ((r >= center.getVectY()) && (r <= center.getVectY() + height)) {
        if (tValue < 0) {
            return -1;
        }
        return tValue;
    } else {
        tValue = (tValue == t1) ? t2 : t1;
    }

    r = ray.origin.getVectY() + tValue * ray.direction.getVectY();
    
    if ((r >= center.getVectY()) && (r <= center.getVectY() + height)) {
        if (tValue < 0) {
            return -1;
        }
        return tValue;
    } else {
        return -1;
    }
}

int Cylinder::getType() {
    return type;
}
