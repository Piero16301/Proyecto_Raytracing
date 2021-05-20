#include <iostream>
#include <vector>
#include <chrono>
#include <pthread.h>
#include <iomanip>

#include "Utils.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "Cylinder.h"

using namespace std;

int FPS = 30;
int duration = 20;
int num_threads = 32;

int step = 0;

double light_move[20] = {0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.45, 0.4, 0.35, 0.3, 0.25, 0.2, 0.15, 0.1, 0.05};

int frames_created = 0;

void* render_frame(void* arg) {

    int temp = step++;

    cout << "Thread " << temp << " renderizando desde el frame " <<  temp * (FPS * duration) / num_threads << " hasta el frame " << (temp + 1) * (FPS * duration) / num_threads << endl;

    for (int i = temp * (FPS * duration) / num_threads; i < (temp + 1) * (FPS * duration) / num_threads; i++) {
        int dpi = 150;
        int width = 1366;
        int height = 768;
        int n = width * height;
        auto *pixels = new RGBType[n];

        const int aadepth = 1; // 1 = deshabilitado, 2 = promedio de 2^2 rayos por pixel
        double aathreshold = 0.1;
        double aspectRatio = (double)width / (double)height;
        double ambientLight = 0.2;
        double accuracy = 0.01;

        // Vectores iniciales
        Vector3D O(0, 0, 0);
        // Vector3D X(1, 0, 0);
        Vector3D Y(0, 1, 0);
        // Vector3D Z(0, 0, 1);

	// Moverse en eje X
        Vector3D sphere1_location(-1 + (light_move[i % 20]), 2.8, -0.6);
        Vector3D sphere2_location(1 + (light_move[i % 20]), 2.8, -0.6);
        Vector3D sphere3_location(0 + (light_move[i % 20]), 2.8, 1.1);

	// Moverse en eje Y
        Vector3D sphere4_location(-1, 1.8 + (light_move[i % 20]), 0.13);
        Vector3D sphere5_location(0.5, 1.8 + (light_move[i % 20]), -1);
        Vector3D sphere6_location(0.7, 1.8 + (light_move[i % 20]), 0.9);

	// Moverse en eje Z
        Vector3D sphere7_location(-0.5, 0.8, -1 + (light_move[i % 20]));
        Vector3D sphere8_location(-0.6, 0.8, 0.8 + (light_move[i % 20]));
        Vector3D sphere9_location(1, 0.8, 0 + (light_move[i % 20]));

        Vector3D cylinder_location(0, 0, 0);

        // Posicion de la camara (plano-luz, alto, plano-sombra)
        double prop = ((double)(20) / (double)(FPS * duration));
        double x_pos = (double)(-10) + (double)(prop * i);
        double z_pos = (double)(-5) + (double)(x_pos);
        // cout << "x_pos: " << x_pos << " z_pos: " << z_pos << " prop: " << prop << endl;
        Vector3D campos(x_pos, 7, z_pos);

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
        Color white(1,1,1,2,0);
        Color red_shiny(1,0,0,0.1,0.5);
        Color green_shiny(0,1,0,0.3,0);
        Color blue_shiny(0,0,1,0.3,0);
        Color black_shiny(0,0,0,0.3,0);
        Color tile_floor(1,1,1,2,0);
        Color yellow_light(1,1,0,0,0);
        Color green_light(0,1,0,0,0);
        Color green_glass((double)126/255,(double)154/255,(double)129/255,0.3,0.3);
        Color blue_glass((double)35/255,(double)172/255,(double)196/255,0.3,0);
        Color orange_glass((double)198/255,(double)151/255,(double)88/255,2,0);
        // Color maroon(0.5, 0.25, 0.25, 0);
        // Color gray(0.5,0.5,0.5,0);
        // Color black(0.0,0.0,0.0,0);

        // Luces de la escena (solo 1)
        Vector3D light_position(-7,10,-10);
        // Light scene_light1(light_position, white);

        Light scene_light1(sphere1_location, green_light);
        Light scene_light2(sphere2_location, green_light);
        Light scene_light3(sphere3_location, green_light);
        Light scene_light4(sphere4_location, green_light);
        Light scene_light5(sphere5_location, green_light);
        Light scene_light6(sphere6_location, green_light);
        Light scene_light7(sphere7_location, green_light);
        Light scene_light8(sphere8_location, green_light);
        Light scene_light9(sphere9_location, green_light);

        vector <Source*> light_sources;
        // light_sources.push_back(dynamic_cast<Source*>(&scene_light1));

        light_sources.push_back(dynamic_cast<Source*>(&scene_light2));
        light_sources.push_back(dynamic_cast<Source*>(&scene_light3));
        light_sources.push_back(dynamic_cast<Source*>(&scene_light4));

        // Objetos de la escena
        Sphere scene_sphere1(sphere1_location, 0.1, green_light);
        Sphere scene_sphere2(sphere2_location, 0.1, green_light);
        Sphere scene_sphere3(sphere3_location, 0.1, green_light);
        Sphere scene_sphere4(sphere4_location, 0.1, green_light);
        Sphere scene_sphere5(sphere5_location, 0.1, green_light);
        Sphere scene_sphere6(sphere6_location, 0.1, green_light);
        Sphere scene_sphere7(sphere7_location, 0.1, green_light);
        Sphere scene_sphere8(sphere8_location, 0.1, green_light);
        Sphere scene_sphere9(sphere9_location, 0.1, green_light);

        Plane scene_plane(Y, 0, orange_glass);
        Cylinder scene_cylinder(cylinder_location, 2, 3, blue_glass);

        vector <Object*> scene_objects;
        scene_objects.push_back(dynamic_cast <Object*> (&scene_sphere1));
        scene_objects.push_back(dynamic_cast <Object*> (&scene_sphere2));
        scene_objects.push_back(dynamic_cast <Object*> (&scene_sphere3));
        scene_objects.push_back(dynamic_cast <Object*> (&scene_sphere4));
        scene_objects.push_back(dynamic_cast <Object*> (&scene_sphere5));
        scene_objects.push_back(dynamic_cast <Object*> (&scene_sphere6));
        scene_objects.push_back(dynamic_cast <Object*> (&scene_sphere7));
        scene_objects.push_back(dynamic_cast <Object*> (&scene_sphere8));
        scene_objects.push_back(dynamic_cast <Object*> (&scene_sphere9));

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
                                /*Color intersection_color;
                                if (scene_objects[index_of_winning_object]->getType() == 1) {
                                    intersection_color = scene_objects[index_of_winning_object]->getColor();
                                } else {
                                    intersection_color = getColorAt(intersection_position, intersecting_ray_direction, scene_objects, index_of_winning_object, light_sources, accuracy, ambientLight);
                                }*/

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

        string frame_route = "/home/piero.morales/CG/Proyecto_Raytracing/images_output/scene_frame_" + to_string(i + 1) + ".bmp";
        saveBMP(frame_route.c_str(), width, height, dpi, pixels);

        delete [] pixels;

	frames_created++;

        cout << "Frame \t" << i + 1 << "\t creado\t|\t" << std::fixed << std::setprecision(3) << ((double)(frames_created * 100) / (double)(FPS * duration)) << "% completado" << endl;
    }

    return (void*) 1;
}

int main() {
    cout << "Renderizando imagen..." << endl;

    auto t1 = chrono::high_resolution_clock::now();

    system("rm /home/piero.morales/CG/Proyecto_Raytracing/images_output/*.bmp");
    system("rm /home/piero.morales/CG/Proyecto_Raytracing/video_output/video.mp4");

    pthread_t threads[num_threads];

    for (int i = 0; i < num_threads; i++) {
        int *p = nullptr;
        pthread_create(&threads[i], nullptr, render_frame, (void*)(p));
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], nullptr);
    }

    string ffmpeg = "ffmpeg -f image2 -framerate " + to_string(FPS) + " -i /home/piero.morales/CG/Proyecto_Raytracing/images_output/scene_frame_%d.bmp /home/piero.morales/CG/Proyecto_Raytracing/video_output/video.mp4";
    system(ffmpeg.c_str());

    auto t2 = chrono::high_resolution_clock::now();

    chrono::duration<double> execution_time = t2 - t1;

    cout << (int)(execution_time.count()) / 60 << " minutos y " << (int)(execution_time.count()) % 60 << " segundos" << endl;

    return 0;
}
