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

Color DefaultRenderer::getObjectColor(Ray &ray, double &t, Object* object) {
	Point3 hitPoint = ray.at(t);
	Vec3 normal = object->getNormal(hitPoint);
	normal.normalize();
	Color finalColor = getAmbientColor(object);
	for (int i = 0; i < lights.size(); i++) {
		Vec3 dir = lights[i]->getDirection(hitPoint);
		if (!intersects(hitPoint, dir)) {
			finalColor += getLightColor(lights[i], object, hitPoint, normal, ray.getDirection(), dir);
		}
	}
	return finalColor;
}

bool DefaultRenderer::intersects(Point3 &p, Vec3 &l) {
	Ray ray(p, l);
	for (int i = 0; i < objects.size(); i++) {
		double t = objects[i]->hit(ray);
		if (!isnan(t) && t > 0.00001) {
			return true;
		}
	}
	return false;
}

double DefaultRenderer::diffuseCoef(Vec3 &normal, Vec3 &light) {
	double r = light.dot(normal);
	if (r > 0) {
		return fmin(1.0, r);
	} else {
		return 0;
	}
}

double DefaultRenderer::specularCoef(double shine, Vec3 &normal, Vec3 &light, Vec3 &ray) {
	Vec3 half = light - ray;
	half.normalize();
	double r = half.dot(normal);
	if (r > 0) {
		return fmin(1.0, pow(r, shine));
	} else {
		return 0
	}
}