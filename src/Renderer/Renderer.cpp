#include "Renderer.h"
#include <iostream>
#include <cstdlib>

Color* Renderer::render(Scene &scene, int width, int height) {
	Color* colors = new Color[width * height];
	float progress = 0;
	int totalProgress = width * height;
	int progressi = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Color c(0, 0, 0);
			for(int s = 0; s < sampleCount; s++) {
				float pixelx = 1.0 * rand() / RAND_MAX + i;
				float pixely = 1.0 * rand() / RAND_MAX + (height - j - 1);
				float x = pixelx / (width - 1);
				float y = pixely / (height - 1);
				Ray ray = scene.camera->getRay(x, y);
				ray.normalize();
				c += getColor(scene, ray, x, y) / sampleCount;
			}
			int newProgress = int(++progress * 100 / totalProgress);
			if (newProgress != progressi) {
				progressi = newProgress;
				std::cout << "\rProgress: " << progressi << '%' << std::flush; 
			}
			colors[j * width + i] = c;
		}
	}
	std::cout << std::endl;
	return colors;
}