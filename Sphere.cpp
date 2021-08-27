#include "Sphere.h"

Sphere::Sphere() {
    center = Vector3D(0,0,0);
    radius = 1.0;
    color = Color(0.5,0.5,0.5,0);
}

Sphere::Sphere(Vector3D centerValue, double radiusValue, Color colorValue) {
    center = centerValue;
    radius = radiusValue;
    color = colorValue;
}

Vector3D Sphere::getSphereCenter() const {
    return center;
}

double Sphere::getSphereRadius() const {
    return radius;
}

Color Sphere::getColor() {
    return color;
}

Vector3D Sphere::getNormalAt(Vector3D point) {
    // Normal always points away from the center of a sphere
    Vector3D normal_Vect = point.vectAdd(center.negative()).normalize();
    return normal_Vect;
}

double Sphere::findIntersection(Ray ray) {
    Vector3D ray_origin = ray.getRayOrigin();
    double ray_origin_x = ray_origin.getVectX();
    double ray_origin_y = ray_origin.getVectY();
    double ray_origin_z = ray_origin.getVectZ();

    Vector3D ray_direction = ray.getRayDirection();
    double ray_direction_x = ray_direction.getVectX();
    double ray_direction_y = ray_direction.getVectY();
    double ray_direction_z = ray_direction.getVectZ();

    Vector3D sphere_center = center;
    double sphere_center_x = sphere_center.getVectX();
    double sphere_center_y = sphere_center.getVectY();
    double sphere_center_z = sphere_center.getVectZ();

    double a = 1;
    double b = (2*(ray_origin_x - sphere_center_x) * ray_direction_x) + (2*(ray_origin_y - sphere_center_y) * ray_direction_y) + (2*(ray_origin_z - sphere_center_z) * ray_direction_z);
    double c = pow(ray_origin_x - sphere_center_x, 2) + pow(ray_origin_y - sphere_center_y, 2) + pow(ray_origin_z - sphere_center_z, 2) - (radius * radius);

    double discriminant = b * b - 4 * c;

    if (discriminant > 0) {
        // Ray intersects the sphere

        // First root
        double root_1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.000001;

        if (root_1 > 0) {
            // First root is th smallest positive
            return root_1;
        } else {
            // Second root is the smallest positive root
            double root_2 = ((sqrt(discriminant) - b) / 2) - 0.000001;
            return root_2;
        }
    } else {
        // Ray doesn't intercept the sphere
        return -1;
    }
}
