#include "DefaultRenderer.h"
#include "../Light/Light.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<float>::infinity()

Color DefaultRenderer::getColor(Scene &scene, Ray &ray, float &x, float &y) {
	Object* hitObject;
	while (true) {
		hitObject = 0;
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
			return getObjectColor(scene, ray, minhr, hitObject);
		} else {
			return scene.backgroundColor(x, y);
		}
	}
}

bool DefaultRenderer::intersects(Scene &scene, Point3 &p, Vec3 &l) {
	Vec3 dir = -l;
	Ray ray(p, dir);
	for (int i = 0; i < scene.objects.size(); i++) {
		HitRecord hr = scene.objects[i]->hit(ray);
		if (!std::isnan(hr.t) && hr.t < -0.00001) {
			return true;
		}
	}
	return false;
}