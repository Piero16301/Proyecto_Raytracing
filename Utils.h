#ifndef ADVANCED_RAYTRACER_UTILS_H
#define ADVANCED_RAYTRACER_UTILS_H

#include <cmath>
#include <vector>

#include "RGBType.h"
#include "Color.h"
#include "Vector3D.h"
#include "Object.h"
#include "Light.h"

using namespace std;

void saveBMP(const char* filename, int w, int h, int dpi, RGBType* data) {
    FILE* f;
    int k = w * h;
    int s = 4 * k;
    int filesize = 54 + s;

    double factor  = 39.375;
    int m = static_cast<int>(factor);

    int ppm = dpi * m;

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};

    bmpfileheader[ 2] = (unsigned char)(filesize);
    bmpfileheader[ 3] = (unsigned char)(filesize>>8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(w);
    bmpinfoheader[ 5] = (unsigned char)(w>>8);
    bmpinfoheader[ 6] = (unsigned char)(w>>16);
    bmpinfoheader[ 7] = (unsigned char)(w>>24);

    bmpinfoheader[ 8] = (unsigned char)(h);
    bmpinfoheader[ 9] = (unsigned char)(h>>8);
    bmpinfoheader[10] = (unsigned char)(h>>16);
    bmpinfoheader[11] = (unsigned char)(h>>24);

    bmpinfoheader[21] = (unsigned char)(s);
    bmpinfoheader[22] = (unsigned char)(s>>8);
    bmpinfoheader[23] = (unsigned char)(s>>16);
    bmpinfoheader[24] = (unsigned char)(s>>24);

    bmpinfoheader[25] = (unsigned char)(ppm);
    bmpinfoheader[26] = (unsigned char)(ppm>>8);
    bmpinfoheader[27] = (unsigned char)(ppm>>16);
    bmpinfoheader[28] = (unsigned char)(ppm>>24);

    bmpinfoheader[29] = (unsigned char)(ppm);
    bmpinfoheader[30] = (unsigned char)(ppm>>8);
    bmpinfoheader[31] = (unsigned char)(ppm>>16);
    bmpinfoheader[32] = (unsigned char)(ppm>>24);

    f = fopen(filename, "wb");

    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);

    for (int i = 0; i < k; i++) {
        double red = (data[i].r) * 255;
        double green = (data[i].g) * 255;
        double blue = (data[i].b) * 255;

        unsigned char color[3] = {(unsigned char)floor(blue), (unsigned char)floor(green), (unsigned char)floor(red)};

        fwrite(color,1,3,f);
    }
    fclose(f);
}

int winningObjectIndex(vector <double> object_intersections) {
    // Se retorna el indice de la menor interseccion
    int index_of_minimum_value;

    // Filtros del tamaño del vector de objetos
    if (object_intersections.empty()) {
        // No hay intersecciones
        return -1;
    }
    else if (object_intersections.size() == 1) {
        if (object_intersections.at(0) > 0) {
            // Si la interseccion es mayor a 0, entonces es la minima
            return 0;
        } else {
            // La unica interseccion es negativa
            return -1;
        }
    } else {
        // Si hay mas de una interseccion
        // Se busca el valor maximo
        double max = 0;
        for (double object_intersection : object_intersections) {
            if (max < object_intersection) {
                max = object_intersection;
            }
        }

        // A partir del maximo valor, se encuentra el minimo
        if (max > 0) {
            // Se busca solo intersecciones positivas
            for (int index = 0; index < object_intersections.size(); index++) {
                if (object_intersections.at(index) > 0 && object_intersections.at(index) <= max) {
                    max = object_intersections.at(index);
                    index_of_minimum_value = index;
                }
            }
            return index_of_minimum_value;
        } else {
            // Todas la intersecciones son negativas
            return -1;
        }
    }
}

Color getColorAt(Vector3D intersection_position, Vector3D intersecting_ray_direction, const vector <Object*>& scene_objects, int index_of_winning_object, const vector <Source*>& light_sources, double accuracy, double ambientLight) {
    // Color del objeto que esta mas al frente
    Color winning_object_color = scene_objects.at(index_of_winning_object)->getColor();

    // Normal del objeto que esta mas al frente
    Vector3D winning_object_normal = scene_objects.at(index_of_winning_object)->getNormalAt(intersection_position);

    if (winning_object_color.getColorSpecial() == 2) {
        // Patron de plano a cuadros
        int square = (int) floor(intersection_position.getVectX()) + (int) floor(intersection_position.getVectZ());
        if ((square % 2) == 0) {
            // Cuadro negro
            winning_object_color.setColorRed(0);
            winning_object_color.setColorGreen(0);
            winning_object_color.setColorBlue(0);
        } else {
            // Cuadro negro
            winning_object_color.setColorRed(1);
            winning_object_color.setColorGreen(1);
            winning_object_color.setColorBlue(1);
        }
    }

    // Color final multiplicado por la luz ambiente
    Color final_color = winning_object_color.colorScalar(ambientLight);

    if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1) {
        // Reflexion de objetos que tienen reflexion especular
        double dot1 = winning_object_normal.dotProduct(intersecting_ray_direction.negative());
        Vector3D scalar1 = winning_object_normal.vectMult(dot1);
        Vector3D add1 = scalar1.vectAdd(intersecting_ray_direction);
        Vector3D scalar2 = add1.vectMult(2);
        Vector3D add2 = intersecting_ray_direction.negative().vectAdd(scalar2);
        Vector3D reflection_direction = add2.normalize();

        Ray reflection_ray(intersection_position, reflection_direction);

        // Determinar el primer objeto con el que se intercepta el rayo
        vector <double> reflection_intersections;
        reflection_intersections.reserve(scene_objects.size());

        for (auto scene_object : scene_objects) {
            reflection_intersections.push_back(scene_object->findIntersection(reflection_ray));
        }

        // Se halla el indice del primer objeto con el que se cruza el rayo de interseccion
        int index_of_winning_object_with_reflection = winningObjectIndex(reflection_intersections);

        if (index_of_winning_object_with_reflection != -1) {
            // El rayo de reflexion no se intersecta con ningun objeto
            if (reflection_intersections.at(index_of_winning_object_with_reflection) > accuracy) {
                // Determinar la posicion y direccion en el punto de interseccion con el rayo de reflexion
                // El rayo solo afecta al color si es reflejado sobre algo
                Vector3D reflection_intersection_position = intersection_position.vectAdd(reflection_direction.vectMult(reflection_intersections.at(index_of_winning_object_with_reflection)));
                Vector3D reflection_intersection_ray_direction = reflection_direction;

                // Se llama recursivamente a esta funcion, para seguir generando rayos hasta que ya no se
                // intercepte con ningun otro objeto
                Color reflection_intersection_color = getColorAt(reflection_intersection_position, reflection_intersection_ray_direction, scene_objects, index_of_winning_object_with_reflection, light_sources, accuracy, ambientLight);

                // Se establece el color final del pixel
                final_color = final_color.colorAdd(reflection_intersection_color.colorScalar(winning_object_color.getColorSpecial()));
            }
        }
    }

    // Se recorren todos las fuentes de luz
    for (auto light_source : light_sources) {
        Vector3D light_direction = light_source->getLightPosition().vectAdd(intersection_position.negative()).normalize();

        // Se halla el coseno entre la interseccion y la luz
        double cosine_angle = winning_object_normal.dotProduct(light_direction);

        if (cosine_angle > 0) {
            // Verifica si la imagen tiene sombra o no
            bool shadowed = false;

            Vector3D distance_to_light = light_source->getLightPosition().vectAdd(intersection_position.negative()).normalize();
            double distance_to_light_magnitude = distance_to_light.magnitude();

            // Rayo desde la interseccion hacia la luz (rayo secundario)
            Ray shadow_ray(intersection_position, light_source->getLightPosition().vectAdd(intersection_position.negative()).normalize());

            // Vector para guardar las intersecciones secundarias
            vector <double> secondary_intersections;
            secondary_intersections.reserve(scene_objects.size());

            // Se calculan las intersecciones del rayo secundario
            for (auto scene_object : scene_objects) {
                secondary_intersections.push_back(scene_object->findIntersection(shadow_ray));
            }

            // Se recorren las intersecciones secundarias
            for (double secondary_intersection : secondary_intersections) {
                if (secondary_intersection > accuracy) {
                    // Si la interseccion es menor o igual a la distancia a la luz, entonces esta en sombra
                    if (secondary_intersection <= distance_to_light_magnitude) {
                        shadowed = true;
                    }
                }
            }

            // Si no esta en sombra, se combina el color del objeto con el color de la luz
            if (!shadowed) {
                final_color = final_color.colorAdd(winning_object_color.colorMultiply(light_source->getLightColor()).colorScalar(cosine_angle));

                // Si el color tiene un valor en special
                if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1) {
                    // Special solo entre [0-1]
                    double dot1 = winning_object_normal.dotProduct(intersecting_ray_direction.negative());
                    Vector3D scalar1 = winning_object_normal.vectMult(dot1);
                    Vector3D add1 = scalar1.vectAdd(intersecting_ray_direction);
                    Vector3D scalar2 = add1.vectMult(2);
                    Vector3D add2 = intersecting_ray_direction.negative().vectAdd(scalar2);
                    Vector3D reflection_direction = add2.normalize();

                    // Reflexion especular
                    double specular = reflection_direction.dotProduct(light_direction);
                    if (specular > 0) {
                        specular = pow(specular, 10);
                        final_color = final_color.colorAdd(light_source->getLightColor().colorScalar(specular * winning_object_color.getColorSpecial()));
                    }
                }
            }
        }
    }
    return final_color.clip();
}

#endif //ADVANCED_RAYTRACER_UTILS_H
