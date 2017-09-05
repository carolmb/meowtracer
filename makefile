OBJS = main.o Sphere.o Light.o DirectionalLight.o BlinnPhongRenderer.o Scene.o Image.o OrthogonalCamera.o PerspectiveCamera.o Renderer.o NormalRenderer.o MapRenderer.o DiffuseRenderer.o InputData.o

CPP_FLAGS= -O3

all: main

main: $(OBJS)
	g++ -o main $(OBJS) -ljson_spirit

main.o: main.cpp
	g++ -c $(CPP_FLAGS) main.cpp

Sphere.o: src/Sphere.cpp
	g++ -c $(CPP_FLAGS) src/Sphere.cpp include/Sphere.h

Light.o: src/Light.cpp
	g++ -c $(CPP_FLAGS) src/Light.cpp include/Light.h

DirectionalLight.o: src/DirectionalLight.cpp
	g++ -c $(CPP_FLAGS) src/DirectionalLight.cpp include/DirectionalLight.h

Scene.o: src/Scene.cpp
	g++ -c $(CPP_FLAGS) src/Scene.cpp include/Scene.h

Image.o: src/Image.cpp
	g++ -c $(CPP_FLAGS) src/Image.cpp include/Image.h

Renderer.o: src/Renderer.cpp
	g++ -c $(CPP_FLAGS) src/Renderer.cpp include/Renderer.h

NormalRenderer.o: src/NormalRenderer.cpp
	g++ -c $(CPP_FLAGS) src/NormalRenderer.cpp include/NormalRenderer.h

MapRenderer.o: src/MapRenderer.cpp
	g++ -c $(CPP_FLAGS) src/MapRenderer.cpp include/MapRenderer.h

DiffuseRenderer.o: src/DiffuseRenderer.cpp
	g++ -c $(CPP_FLAGS) src/DiffuseRenderer.cpp include/DiffuseRenderer.h

BlinnPhongRenderer.o: src/BlinnPhongRenderer.cpp
	g++ -c $(CPP_FLAGS) src/BlinnPhongRenderer.cpp include/BlinnPhongRenderer.h

InputData.o: src/InputData.cpp
	g++ -c $(CPP_FLAGS) src/InputData.cpp include/InputData.h

OrthogonalCamera.o: src/OrthogonalCamera.cpp
	g++ -c $(CPP_FLAGS) src/OrthogonalCamera.cpp include/OrthogonalCamera.h

PerspectiveCamera.o: src/PerspectiveCamera.cpp
	g++ -c $(CPP_FLAGS) src/PerspectiveCamera.cpp include/PerspectiveCamera.h

clean:
	rm -f *.o *~ include/*.h.gch