cmake_minimum_required(VERSION 3.19)
project(Advanced_Raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-lX11")
set(CMAKE_CXX_FLAGS "-lpthread")
set(CMAKE_CXX_FLAGS "-ljpeg")

add_executable(Advanced_Raytracer main.cpp CImg.h Vector3D.cpp Vector3D.h Ray.cpp Ray.h RGBType.cpp RGBType.h Utils.h Camera.cpp Camera.h Color.cpp Color.h Light.cpp Light.h Sphere.cpp Sphere.h Object.cpp Object.h Plane.cpp Plane.h Source.cpp Source.h Cylinder.cpp Cylinder.h)

target_link_libraries(Advanced_Raytracer -lX11 -lpthread -ljpeg)