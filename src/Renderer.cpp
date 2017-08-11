#include "../include/Renderer.h"

Color* Renderer::render(Scene &scene, int width, int height) {
	Color* colors = new Color[width * height];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			double x = 1.0 * i / (width - 1);
			double y = 1.0 * j / (height - 1);
			Ray ray = scene.camera->getRay(x, y);
			colors[j * width + i] = getColor(scene, ray, x, y);
		}
	}
	return colors;
}

Color Renderer::getColor(Scene &scene, Ray &ray, double x, double y) {
	if (scene.sphere.hits(ray)) {
		return Color(255, 0, 255);
	} else {
		return scene.backgroundColor(x, y);
	}
}