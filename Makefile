OBJ = Camera.o Color.o Cylinder.o Light.o Object.o Plane.o RGBType.o Ray.o Source.o Sphere.o Vector3D.o main.o

Advanced_Raytracer: $(OBJ)
	g++ $(OBJ) -o Advanced_Raytracer.exe
	del /f $(OBJ)
	.\Advanced_Raytracer.exe

main.o:
	g++ -c Camera.cpp Color.cpp Cylinder.cpp Light.cpp Object.cpp Plane.cpp RGBType.cpp Ray.cpp Source.cpp Sphere.cpp Vector3D.cpp main.cpp

clean:
	del /f $(OBJ) Advanced_Raytracer.exe