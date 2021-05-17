#include <iostream>
#include <vector>
#include <chrono>

#include "Utils.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "Cylinder.h"
#include "CImg.h"

using namespace std;

int main() {
    cout << "Renderizando imagen..." << endl;

    auto t1 = chrono::high_resolution_clock::now();

    system("del /f images_output\\*.bmp");
    system("del /f video_output\\video.mp4");

    int FPS = 1;
    int duration = 1;

    for (int frame_number = 0; frame_number < (FPS * duration); frame_number++) {
        int dpi = 144;
        int width = 1280;
        int height = 720;
        int n = width * height;
        auto *pixels = new RGBType[n];

        const int aadepth = 1; // 1 = deshabilitado, 2 = promedio de 2^2 rayos por pixel
        double aathreshold = 0.1;
        double aspectRatio = (double)width / (double)height;
        double ambientLight = 0.2;
        double accuracy = 0.000001;

        // Vectores iniciales
        Vector3D O(0, 0, 0);
        // Vector3D X(1, 0, 0);
        Vector3D Y(0, 1, 0);
        // Vector3D Z(0, 0, 1);
        Vector3D sphere2_location(4, 0, 0);
        Vector3D sphere3_location(0, 0, 4);
        Vector3D cylinder_location(0, 0, -2);

        // Posicion de la camara (plano-luz, alto, plano-sombra)
        Vector3D campos(5, 3, (-9 + ((double)(18 / (double)(FPS * duration)) * frame_number)));

        // Direccion de la camara
        Vector3D look_at(0,0,0);
        Vector3D diff_btw(campos.getVectX() - look_at.getVectX(),
                        campos.getVectY() - look_at.getVectY(),
                        campos.getVectZ() - look_at.getVectZ());

        Vector3D camdir = diff_btw.negative().normalize();
        Vector3D camright = Y.crossProduct(camdir).normalize();
        Vector3D camdown = camright.crossProduct(camdir);

        // Objeto camara de la escena
        Camera scene_cam(campos, camdir, camright, camdown);

        // Colores pre-definidos
        Color white(1,1,1,0);
        Color red_shiny(1,0,0,0.3);
        Color green_shiny(0,1,0,0.3);
        Color blue_shiny(0,0,1,0.3);
        Color tile_floor(1, 1, 1, 2);
        // Color maroon(0.5, 0.25, 0.25, 0);
        // Color gray(0.5,0.5,0.5,0);
        // Color black(0.0,0.0,0.0,0);

        // Luces de la escena (solo 1)
        Vector3D light_position(-7,10,-10);
        Light scene_light(light_position, white);
        vector <Source*> light_sources;
        light_sources.push_back(dynamic_cast<Source*>(&scene_light));

        // Objetos de la escena
        // Sphere scene_sphere1(O, 1, red_shiny);
        Sphere scene_sphere2(sphere2_location, 1, green_shiny);
        Sphere scene_sphere3(sphere3_location, 1, blue_shiny);
        Plane scene_plane(Y, -1, tile_floor);
        Cylinder scene_cylinder(cylinder_location, 1, 1, red_shiny);

        vector <Object*> scene_objects;
        // scene_objects.push_back(dynamic_cast <Object*> (&scene_sphere1));
        scene_objects.push_back(dynamic_cast <Object*> (&scene_sphere2));
        scene_objects.push_back(dynamic_cast <Object*> (&scene_sphere3));
        scene_objects.push_back(dynamic_cast <Object*> (&scene_plane));
        scene_objects.push_back(dynamic_cast <Object*> (&scene_cylinder));

        int thisone;
        int aa_index;

        double xamnt;
        double yamnt;

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                thisone = y * width + x;

                // Se comienza con un pixel blanco
                double tempRed[aadepth * aadepth];
                double tempGreen[aadepth * aadepth];
                double tempBlue[aadepth * aadepth];

                for (int aax = 0; aax < aadepth; aax++) {
                    for (int aay = 0; aay < aadepth; aay++) {

                        aa_index = aay * aadepth + aax;

                        srand(time(nullptr));

                        // Se crea el rayo desde la camara hacia este pixel

                        if (aadepth == 1) {
                            // Sin anti-aliasing
                            if (width > height) {
                                // El ancho es mayor que el alto
                                xamnt = ((x + 0.5) / width) * aspectRatio - (((width - height) / (double)height) / 2);
                                yamnt = ((height - y) + 0.5) / height;
                            }
                            else if (height > width) {
                                // El alto es mayor que el ancho
                                xamnt = (x + 0.5) / width;
                                yamnt = (((height - y) + 0.5) / height) / aspectRatio - (((height - width) / (double)width) / 2);
                            } else {
                                // Imagen cuadrada
                                xamnt = (x + 0.5) / width;
                                yamnt = ((height - y) + 0.5) / height;
                            }
                        } else {
                            // Con anti-aliasing
                            if (width > height) {
                                // El ancho es mayor que el alto
                                xamnt = ((x + (double)aax / ((double)aadepth - 1)) / width) * aspectRatio - (((width - height) / (double)height) / 2);
                                yamnt = ((height - y) + (double)aax / ((double)aadepth - 1)) / height;
                            }
                            else if (height > width) {
                                // El alto es mayor que el ancho
                                xamnt = (x + (double)aax / ((double)aadepth - 1)) / width;
                                yamnt = (((height - y) + (double)aax / ((double)aadepth - 1)) / height) / aspectRatio - (((height - width) / (double)width) / 2);
                            } else {
                                // Imagen cuadrada
                                xamnt = (x + (double)aax / ((double)aadepth - 1)) / width;
                                yamnt = ((height - y) + (double)aax / ((double)aadepth - 1)) / height;
                            }
                        }

                        // Origen y direccion del rayo para este pixel
                        Vector3D cam_ray_origin = scene_cam.getCameraPosition();
                        Vector3D cam_ray_direction = camdir.vectAdd(camright.vectMult(xamnt - 0.5).vectAdd(camdown.vectMult(yamnt - 0.5))).normalize();

                        Ray cam_ray(cam_ray_origin, cam_ray_direction);

                        // Se guardan las intersecciones
                        vector <double> intersections;
                        intersections.reserve(scene_objects.size());

                        // Se encuentran todas las intersecciones con los objetos
                        for (auto & scene_object : scene_objects) {
                            intersections.push_back(scene_object->findIntersection(cam_ray));
                        }

                        // Se calcula el objeto que se encuentra mas adelante de la camara
                        int index_of_winning_object = winningObjectIndex(intersections);

                        // Si no hay ninguna interseccion, se pinta de negro
                        if (index_of_winning_object == -1) {
                            tempRed[aa_index] = 0;
                            tempGreen[aa_index] = 0;
                            tempBlue[aa_index] = 0;
                        } else {
                            // Ya se tiene el indice del objeto mas cercano
                            if (intersections.at(index_of_winning_object) > accuracy) {
                                // Se calcula el color del pixel a partir de la posicion y direccion de los vectores en el punto de interseccion
                                Vector3D intersection_position = cam_ray_origin.vectAdd(cam_ray_direction.vectMult(intersections.at(index_of_winning_object)));
                                Vector3D intersecting_ray_direction = cam_ray_direction;

                                Color intersection_color = getColorAt(intersection_position, intersecting_ray_direction, scene_objects, index_of_winning_object, light_sources, accuracy, ambientLight);

                                // Se asigna los valores RGB del pixel a la imagen final
                                tempRed[aa_index] = intersection_color.getColorRed();
                                tempGreen[aa_index] = intersection_color.getColorGreen();
                                tempBlue[aa_index] = intersection_color.getColorBlue();
                            }
                        }
                    }
                }

                // Promedio del color del pixel
                double totalRed = 0;
                double totalGreen = 0;
                double totalBlue = 0;

                for (int iRed = 0; iRed < aadepth * aadepth; iRed++) {
                    totalRed = totalRed + tempRed[iRed];
                }
                for (int iGreen = 0; iGreen < aadepth * aadepth; iGreen++) {
                    totalGreen = totalGreen + tempGreen[iGreen];
                }
                for (int iBlue = 0; iBlue < aadepth * aadepth; iBlue++) {
                    totalBlue = totalBlue + tempBlue[iBlue];
                }

                double avgRed = totalRed / (aadepth * aadepth);
                double avgGreen = totalGreen / (aadepth * aadepth);
                double avgBlue = totalBlue / (aadepth * aadepth);

                pixels[thisone].r = avgRed;
                pixels[thisone].g = avgGreen;
                pixels[thisone].b = avgBlue;
            }
        }

        /*cimg_library::CImg<double> image(width, height, 1, 3, 255);

        int y_counter = height-1;
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int thisone = y * width + x;
                image(x, y_counter, 0, 0) = pixels[thisone].r;
                image(x, y_counter, 0, 1) = pixels[thisone].g;
                image(x, y_counter, 0, 2) = pixels[thisone].b;
                y_counter--;
            }
            y_counter = height-1;
        }

        image.display();*/

        // Se borra la imagen anterior y se crea la nueva
        // system("del /f ..\\scene.bmp");
        // saveBMP("../scene.bmp",width,height,dpi,pixels);
        // system("rm images_output/scene.bmp");
        string frame_route = "images_output\\scene_frame_" + to_string(frame_number + 1) + ".bmp";
        saveBMP(frame_route.c_str(), width, height, dpi, pixels);

        delete [] pixels;

        cout << "Frame " << frame_number + 1 << " creado" << endl;
    }

    string ffmpeg = "ffmpeg -f image2 -framerate " + to_string(FPS) + " -i images_output/scene_frame_%d.bmp video_output/video.mp4";
    system(ffmpeg.c_str());

    auto t2 = chrono::high_resolution_clock::now();

    /*cimg_library::CImg<unsigned char> img("../images_output/scene_frame_1.bmp");
    img.display();*/

    chrono::duration<double> execution_time = t2 - t1;

    cout << (int)(execution_time.count()) / 60 << " minutos y " << (int)(execution_time.count()) % 60 << " segundos" << endl;

    return 0;
}