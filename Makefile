OBJ = main.o Vector3D.o Ray.o RGBType.o Camera.o Color.o Light.o Sphere.o Object.o Plane.o Source.o Cylinder.o

Advanced_Raytracer: $(OBJ)
	g++ -std=c++11 $(OBJ) -o Advanced_Raytracer -pthread
	rm $(OBJ)

main.o:
	g++ -std=c++11 -c main.cpp Vector3D.cpp Ray.cpp RGBType.cpp Camera.cpp Color.cpp Light.cpp Sphere.cpp Object.cpp Plane.cpp Source.cpp Cylinder.cpp

clean:
	rm $(OBJ) Advanced_Raytracer

