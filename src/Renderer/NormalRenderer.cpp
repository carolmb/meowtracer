#include "NormalRenderer.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<float>::infinity()

Color NormalRenderer::getColor(Scene &scene, Ray &ray, float &x, float &y) {
	int depth = 0;
	Object* hitObject = 0;
	HitRecord minhr;
	minhr.t = INF;
	for (int i = 0; i < scene.objects.size(); i++) {
		HitRecord hr = scene.objects[i]->hit(ray);
		if (!std::isnan(hr.t) && hr.t < minhr.t && hr.t > 0) {
			minhr = hr;
			hitObject = scene.objects[i];
		}
	}
	if (hitObject) {
		float r = (minhr.normal.x + 1) / 2;
		float g = (minhr.normal.y + 1) / 2;
		float b = (minhr.normal.z + 1) / 2;
		return Color(r, g, b);
	} else {
		return scene.backgroundColor(x, y);
	}
}
