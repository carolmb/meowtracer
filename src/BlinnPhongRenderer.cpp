#include "../include/BlinnPhongRenderer.h"
#include "../include/Light.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<double>::infinity()

bool intersects(Scene &scene, Point3 &p, Vec3 &l) {
	Ray ray(p, l);
	for (int i = 0; i < scene.objects.size(); i++) {
		double t = scene.objects[i]->hit(ray);
		if (!isnan(t) && t > 0.00001) {
			return true;
		}
	}
	return false;
}

Color BlinnPhongRenderer::getColor(Scene &scene, Ray &ray, double &x, double &y) {
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

Color BlinnPhongRenderer::getObjectColor(Scene &scene, Ray &ray, double &t, Object* object) {
	Point3 hitPoint = ray.at(t);
	Vec3 n = object->getNormal(hitPoint);
	Vec3 v = ray.getDirection();
	n.normalize();
	Color finalColor(0, 0, 0);
	for (int i = 0; i < scene.lights.size(); i++) {
		Vec3 dir = scene.lights[i]->getDirection(hitPoint);
		if (!intersects(scene, hitPoint, dir)) {
			finalColor += scene.lights[i]->diffuseColor(object->material, n, dir);
			finalColor += scene.lights[i]->specularColor(object->material, n, dir, v);
		}
	}
	finalColor += object->material->ambient * scene.ambientColor;
	return finalColor;
}
