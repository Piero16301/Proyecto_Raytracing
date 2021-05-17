#include "Light.h"

Light::Light() {
    position = Vector3D(0,0,0);
    color = Color(1,1,1,0);
}

Light::Light(Vector3D p, Color c) {
    position = p;
    color = c;
}

Vector3D Light::getLightPosition() {
    return position;
}

Color Light::getLightColor() {
    return color;
}
