#include "CelRenderer.h"
#include "../Light/Light.h"
#include "RendererUtil.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<float>::infinity()

Color CelRenderer::getColor(Scene &scene, Ray &ray, float &x, float &y) {
	RayHit hr = getHit(ray);
	if (hr.object) {
		Vec3 v = -ray.direction;
		float cos = Vec3::Dot(v, hr.normal);
		if (cos < hr.object->material->outlineAngle) {
			return hr.object->material->outlineColor;
		}
		Color c = hr.object->material->ambient * scene.ambientColor;
		float l = -1;
		LightHit lh(ray.direction, hr);
		for (int i = 0; i < scene.lights.size(); i++) {
			Vec3 dir = scene.lights[i]->getDirection(lh);
			dir = Vec3::Normalize(dir);
			float cos = Vec3::Dot(dir, hr.normal);
			if (!intersects(scene, hr.point, dir)) {
				l = fmax(l, cos);
			}
		}
		for (int i = 0; i < hr.object->material->times.size(); i++) {
			if (l < hr.object->material->times[i]) {
				return c + hr.object->material->colors[i];
			}
		}
		return c + hr.object->material->colors[hr.object->material->colors.size() - 1];
	} else {
		return scene.backgroundColor(x, y);
	}
}