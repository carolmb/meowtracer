#include "../include/Renderer.h"

Color* Renderer::render(Camera* camera, int width, int height) {
	Color* colors = new Color[rowCount * colCount];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			double x = i / width;
			double y = j / height;
			Ray ray = camera->getRay(x, y);
			colors[i * width + j] = getColor(ray);
		}
	}
	return colors;
}

Color Renderer::getColor(Ray &ray) {
	Sphere sphere = Sphere(Point3(0, 0, 0), 1);
	if (sphere.hits(ray)) {
		return Color(255, 0, 255);
	} else {
		return Color(0, 0, 0);
	}
}