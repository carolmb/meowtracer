OBJS = main.o Color.o Sphere.o Scene.o MeowImage.o OrthogonalCamera.o PerspectiveCamera.o Renderer.o NormalRenderer.o MapRenderer.o InputData.o

all: main clean

main: $(OBJS)
	g++ -o main $(OBJS) -ljson_spirit

main.o: main.cpp
	g++ -c main.cpp

Color.o: src/Color.cpp
	g++ -c src/Color.cpp include/Color.h

Sphere.o: src/Sphere.cpp
	g++ -c src/Sphere.cpp include/Sphere.h

Scene.o: src/Scene.cpp
	g++ -c src/Scene.cpp include/Scene.h

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

Renderer.o: src/Renderer.cpp
	g++ -c src/Renderer.cpp include/Renderer.h

NormalRenderer.o: src/NormalRenderer.cpp
	g++ -c src/NormalRenderer.cpp include/NormalRenderer.h

MapRenderer.o: src/MapRenderer.cpp
	g++ -c src/MapRenderer.cpp include/MapRenderer.h

clean:
	rm -f *.o *~ include/*.h.gch