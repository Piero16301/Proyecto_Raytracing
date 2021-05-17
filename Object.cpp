#include "Object.h"

Color Object::getColor() {
    return Color(0.0,0.0,0.0,0);
}

Vector3D Object::getNormalAt(Vector3D point) {
    return Vector3D(0,0,0);
}

double Object::findIntersection(Ray ray) {
    return 0;
}

int Object::getType() {
    return 0;
}
