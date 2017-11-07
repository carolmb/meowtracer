#include "DefaultRenderer.h"
#include "../Light/Light.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<float>::infinity()

Color DefaultRenderer::getColor(Scene &scene, Ray &ray, float &x, float &y) {
	Object* hitObject;
	while (true) {
		hitObject = 0;
		float mint = INF;
		for (int i = 0; i < scene.objects.size(); i++) {
			float t = scene.objects[i]->hit(ray);
			if (!isnan(t) && t < mint && t > 0) {
				mint = t;
				hitObject = scene.objects[i];
			}
		}
		if (hitObject) {
			return getObjectColor(scene, ray, mint, hitObject);
		} else {
			return scene.backgroundColor(x, y);
		}
	}
}

bool DefaultRenderer::intersects(Scene &scene, Point3 &p, Vec3 &l) {
	Ray ray(p, l);
	for (int i = 0; i < scene.objects.size(); i++) {
		float t = scene.objects[i]->hit(ray);
		if (!isnan(t) && t > 0.00001) {
			return true;
		}
	}
	return false;
}