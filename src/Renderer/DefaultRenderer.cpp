#include "../../include/Renderer/DefaultRenderer.h"
#include "../../include/Light.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<double>::infinity()

Color DefaultRenderer::getColor(Scene &scene, Ray &ray, double &x, double &y) {
	Object* hitObject;
	while (true) {
		hitObject = 0;
		double mint = INF;
		for (int i = 0; i < scene.objects.size(); i++) {
			double t = scene.objects[i]->hit(ray);
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
		double t = scene.objects[i]->hit(ray);
		if (!isnan(t) && t > 0.00001) {
			return true;
		}
	}
	return false;
}