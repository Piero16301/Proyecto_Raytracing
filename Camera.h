#ifndef ADVANCED_RAYTRACER_CAMERA_H
#define ADVANCED_RAYTRACER_CAMERA_H

#include "Vector3D.h"

class Camera {
public:
    Vector3D campos;
    Vector3D camdir;
    Vector3D camright;
    Vector3D camdown;

public:
    Camera();
    Camera(Vector3D pos, Vector3D dir, Vector3D right, Vector3D down);

    Vector3D getCameraPosition() const;
    Vector3D getCameraDirection() const;
    Vector3D getCameraRight() const;
    Vector3D getCameraDown() const;
};

#endif //ADVANCED_RAYTRACER_CAMERA_H
