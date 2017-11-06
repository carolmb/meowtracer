#include "Renderer.h"
#include <iostream>
#include <cstdlib>

Color* Renderer::render(int width, int height) {
	Color* colors = new Color[width * height];
	double progress = 0;
	int totalProgress = width * height;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Color c(0, 0, 0);
			for(int s = 0; s < sampleCount; s++) {
				double pixelx = 1.0 * rand() / RAND_MAX + i;
				double pixely = 1.0 * rand() / RAND_MAX + (height - j - 1);
				double x = pixelx / (width - 1);
				double y = pixely / (height - 1);
				Ray ray = camera->getRay(x, y);
				ray.normalize();
				c += getColor(ray, x, y) / sampleCount;
			}
			std::cout << "\rProgress: " << int(++progress * 100 / totalProgress) << '%' << std::flush; 
			colors[j * width + i] = c;
		}
	}
	std::cout << std::endl;
	return colors;
}

Color Renderer::backgroundColor(double tCol, double tRow)  {
	Color top = tl.lerp(tr, tCol);
	Color bottom = bl.lerp(br, tCol);
	return top.lerp(bottom, tRow);
}