OBJS = main.o Sphere.o Scene.o MeowImage.o OrthogonalCamera.o PerspectiveCamera.o Renderer.o NormalRenderer.o MapRenderer.o DiffuseRenderer.o InputData.o

CPP_FLAGS=-O3

all: main

main: $(OBJS)
	g++ -o main $(OBJS) -ljson_spirit

main.o: main.cpp
	g++ -c $(CPP_FLAGS) main.cpp

Sphere.o: src/Sphere.cpp
	g++ -c $(CPP_FLAGS) src/Sphere.cpp include/Sphere.h

Scene.o: src/Scene.cpp
	g++ -c $(CPP_FLAGS) src/Scene.cpp include/Scene.h

MeowImage.o: src/MeowImage.cpp
	g++ -c $(CPP_FLAGS) src/MeowImage.cpp include/MeowImage.h

Renderer.o: src/Renderer.cpp
	g++ -c $(CPP_FLAGS) src/Renderer.cpp include/Renderer.h

NormalRenderer.o: src/NormalRenderer.cpp
	g++ -c $(CPP_FLAGS) src/NormalRenderer.cpp include/NormalRenderer.h

MapRenderer.o: src/MapRenderer.cpp
	g++ -c $(CPP_FLAGS) src/MapRenderer.cpp include/MapRenderer.h

DiffuseRenderer.o: src/DiffuseRenderer.cpp
	g++ -c $(CPP_FLAGS) src/DiffuseRenderer.cpp include/DiffuseRenderer.h

InputData.o: src/InputData.cpp
	g++ -c $(CPP_FLAGS) src/InputData.cpp include/InputData.h

OrthogonalCamera.o: src/OrthogonalCamera.cpp
	g++ -c $(CPP_FLAGS) src/OrthogonalCamera.cpp include/OrthogonalCamera.h

PerspectiveCamera.o: src/PerspectiveCamera.cpp
	g++ -c $(CPP_FLAGS) src/PerspectiveCamera.cpp include/PerspectiveCamera.h

clean:
	rm -f *.o *~ include/*.h.gch