#include "Camera.h"

Camera::Camera() {
    campos = Vector3D(0,0,0);
    camdir = Vector3D(0,0,1);
    camright = Vector3D(0,0,0);
    camdown = Vector3D(0,0,0);
}

Camera::Camera(Vector3D pos, Vector3D dir, Vector3D right, Vector3D down) {
    campos = pos;
    camdir = dir;
    camright = right;
    camdown = down;
}

Vector3D Camera::getCameraPosition() const {
    return campos;
}

Vector3D Camera::getCameraDirection() const {
    return camdir;
}

Vector3D Camera::getCameraRight() const {
    return camright;
}

Vector3D Camera::getCameraDown() const {
    return camdown;
}
