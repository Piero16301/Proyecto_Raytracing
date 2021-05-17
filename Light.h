#ifndef ADVANCED_RAYTRACER_LIGHT_H
#define ADVANCED_RAYTRACER_LIGHT_H

#include "Source.h"
#include "Vector3D.h"
#include "Color.h"

class Light : public Source {
public:
    Vector3D position;
    Color color;

public:
    Light();
    Light(Vector3D p, Color c);

    Vector3D getLightPosition() override;
    Color getLightColor() override;
};

#endif //ADVANCED_RAYTRACER_LIGHT_H
