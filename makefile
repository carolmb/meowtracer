main: main.o Color.o Sphere.o MeowImage.o OrthogonalCamera.o PerspectiveCamera.o InputData.o Renderer.o
	g++ -o main main.o Color.o Sphere.o MeowImage.o OrthogonalCamera.o PerspectiveCamera.o InputData.o Renderer.o

main.o: main.cpp
	g++ -c main.cpp

Color.o: src/Color.cpp
	g++ -c src/Color.cpp include/Color.h

Sphere.o: src/Sphere.cpp
	g++ -c src/Sphere.cpp include/Sphere.h

MeowImage.o: src/MeowImage.cpp
	g++ -c src/MeowImage.cpp include/MeowImage.h

Renderer.o: src/Renderer.cpp
	g++ -c src/Renderer.cpp include/Renderer.h

InputData.o: src/InputData.cpp
	g++ -c src/InputData.cpp include/InputData.h

OrthogonalCamera.o: src/OrthogonalCamera.cpp
	g++ -c src/OrthogonalCamera.cpp include/OrthogonalCamera.h

PerspectiveCamera.o: src/PerspectiveCamera.cpp
	g++ -c src/PerspectiveCamera.cpp include/PerspectiveCamera.h