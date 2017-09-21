#include "../../include/Renderer/CelRenderer.h"
#include "../../include/Light.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<double>::infinity()

Color CelRenderer::getObjectColor(Scene &scene, Ray &ray, double &t, Object* object) {
	Point3 hitPoint = ray.at(t);
	Vec3 n = object->getNormal(hitPoint);
	Vec3 v = ray.getDirection();
	double cos = (-v).dot(n);
	if (cos < object->material->outlineAngle) {
		return object->material->outlineColor;
	}
	Color c = object->material->ambient * scene.ambientColor;
	double l = 0;
	for (int i = 0; i < scene.lights.size(); i++) {
		Vec3 dir = scene.lights[i]->getDirection(hitPoint);
		dir.normalize();
		double cos = dir.dot(n);
		if (cos > 0 && !intersects(scene, hitPoint, dir)) {
			l += fmin(1.0, cos);
		}
	}
	for (int i = 0; i < object->material->times.size(); i++) {
		if (l < object->material->times[i]) {
			return c + object->material->colors[i];
		}
	}
	return c + object->material->colors[object->material->colors.size() - 1];
}
