#include "../include/Renderer.h"
#include <cmath>
#include <limits>
#include <iostream>
#define INF std::numeric_limits<double>::infinity()

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

double Renderer::getDepth(Scene &scene, Ray &ray) {
	Sphere* hitSphere;
	double mint = NAN;
	for (int i = 0; i < scene.spheres.size(); i++) {
		double t = scene.spheres[i].hit(ray);
		if (isnan(mint) || !isnan(t) && t < mint) {
			mint = t;
		}
	}
	if (hitSphere) {
		Point3 p = ray.at(mint);
		return p.z;
	} else {
		return NAN;
	}
}

Color Renderer::getColor(Scene &scene, Ray &ray, double x, double y) {
	Sphere* hitSphere = 0;
	double mint = INF;
	for (int i = 0; i < scene.spheres.size(); i++) {
		double t = scene.spheres[i].hit(ray);
		if (!isnan(t) && t < mint && t > 0) {
			mint = t;
			hitSphere = &scene.spheres[i];
		}
	}
	if (hitSphere) {
		return hitSphere->getColor(ray, mint);
	} else {
		return scene.backgroundColor(x, y);
	}
}