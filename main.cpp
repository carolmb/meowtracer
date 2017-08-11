#include <iostream>
#include <string>
#include "include/Color.h"
#include "include/Vec3.h"
#include "include/MeowImage.h"
#include "include/Renderer.h"
#include "include/OrthogonalCamera.h"

void printSphere(std::string &fileName) {
	int width = 100;
	int height = 100;
	Renderer renderer = Renderer();
	Camera* camera = new OrthogonalCamera();
	Color* colors = renderer.render(camera, width, height);
	MeowImage img(true, width, height, fileName, colors);
	img.ppm();
}

void readGradient(std::string &fileName) {
	MeowImage img = MeowImage::gradient(fileName);
	img.ppm();
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		std::string fileName = argv[1];
		//readGradient(fileName);
		printSphere(fileName);
	} else {
		std::cout << "File name must be specified." << std::endl;
	}
	return 0;
}