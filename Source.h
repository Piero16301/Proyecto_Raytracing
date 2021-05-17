#ifndef ADVANCED_RAYTRACER_SOURCE_H
#define ADVANCED_RAYTRACER_SOURCE_H

#include "Vector3D.h"
#include "Color.h"

class Source {
public:
    Source() = default;

    virtual Vector3D getLightPosition();
    virtual Color getLightColor();
};

#endif //ADVANCED_RAYTRACER_SOURCE_H
