#include "../include/NormalRenderer.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<double>::infinity()

Color NormalRenderer::getColor(Scene &scene, Ray &ray, double x, double y) {
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