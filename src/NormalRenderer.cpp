#include "../include/NormalRenderer.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<double>::infinity()

Color NormalRenderer::getColor(Scene &scene, Ray &ray, double x, double y) {
	Object* hitObject = 0;
	double mint = INF;
	for (int i = 0; i < scene.objects.size(); i++) {
		double t = scene.objects[i]->hit(ray);
		if (!isnan(t) && t < mint && t > 0) {
			mint = t;
			hitObject = scene.objects[i];
		}
	}
	if (hitObject) {
		return hitObject->getColor(ray, mint);
	} else {
		return scene.backgroundColor(x, y);
	}
}