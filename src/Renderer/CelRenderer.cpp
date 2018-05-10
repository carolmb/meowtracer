#include "CelRenderer.h"
#include "../Light/Light.h"
#include "RendererUtil.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<float>::infinity()

Color CelRenderer::getColor(Scene &scene, Ray &ray, float &x, float &y) {
	RayHit rh = getHit(ray);
	if (rh.object) {
		Vec3 v = -ray.direction;
		float cos = Vec3::Dot(v, rh.normal);
		if (cos < rh.object->material->outlineAngle) {
			return rh.object->material->outlineColor;
		}
		Color c = rh.object->material->ambient * scene.ambientColor;
		float l = -1;
		for (int i = 0; i < scene.lights.size(); i++) {
			LightHit lh = scene.lights[i]->getHit(ray.direction, rh);
			float cos = Vec3::Dot(lh.lightDir, rh.normal);
			if (!intersects(scene, lh)) {
				l = fmax(l, cos);
			}
		}
		for (int i = 0; i < rh.object->material->times.size(); i++) {
			if (l < rh.object->material->times[i]) {
				return c + rh.object->material->colors[i];
			}
		}
		return c + rh.object->material->colors[rh.object->material->colors.size() - 1];
	} else {
		return scene.backgroundColor(x, y);
	}
}