#include "../include/Renderer.h"
#include <iostream>

Color* Renderer::render(Scene &scene, int width, int height) {
	Color* colors = new Color[width * height];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			double x = 1.0 * i / (width - 1);
			double y = 1.0 * (height - j - 1) / (height - 1);
			Ray ray = scene.camera->getRay(x, y);
			colors[j * width + i] = getColor(scene, ray, x, y);
		}
	}
	return colors;
}