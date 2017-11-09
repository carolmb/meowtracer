#include "CelRenderer.h"
#include "../Light/Light.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<float>::infinity()

Color CelRenderer::getObjectColor(Scene &scene, Ray &ray, HitRecord &hr, Object* object) {
	Vec3 v = -ray.direction;
	float cos = Vec3::Dot(v, hr.normal);
	if (cos < object->material->outlineAngle) {
		return object->material->outlineColor;
	}
	Color c = object->material->ambient * scene.ambientColor;
	float l = -1;
	for (int i = 0; i < scene.lights.size(); i++) {
		Vec3 dir = scene.lights[i]->getDirection(hr.point);
		dir = Vec3::Normalize(dir);
		float cos = Vec3::Dot(dir, hr.normal);
		if (!intersects(scene, hr.point, dir)) {
			l = fmax(l, cos);
		}
	}
	for (int i = 0; i < object->material->times.size(); i++) {
		if (l < object->material->times[i]) {
			return c + object->material->colors[i];
		}
	}
	return c + object->material->colors[object->material->colors.size() - 1];
}
