#include "../include/Renderer.h"
#include <iostream>
#include <cstdlib>

Color* Renderer::render(Scene &scene, int width, int height) {
	Color* colors = new Color[width * height];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			double pixelx = 1.0 * i;
			double pixely = 1.0 * (height - j - 1);
			double x = pixelx / (width - 1);
			double y = pixely / (height - 1);
			Ray ray = scene.camera->getRay(x, y);
			ray.normalize();
			colors[j * width + i] = getColor(scene, ray, x, y);
		}
	}
	return colors;
}