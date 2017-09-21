#include "../../include/Renderer/DiffuseRenderer.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iostream>
#define INF std::numeric_limits<double>::infinity()
#define PI2 6.28318530718 

Color DiffuseRenderer::getColor(Scene &scene, Ray &initRay, double &x, double &y) {
	int depth = 0;
	Object* hitObject;
	Ray ray = initRay;
	Color color(1, 1, 1);
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
			color *= getObjectColor(scene, ray, mint, hitObject);
			if (depth >= rayCount) {
				break;
			} else {
				Point3 hitPoint = ray.at(mint);
				Vec3 n = hitObject->getNormal(hitPoint);
				Point3 d = n + randomUnitVec3();
				ray = Ray(hitPoint, d);
			}
		} else {
			color *= scene.backgroundColor(x, y);
			break;
		}
	}
	return color;
}

Vec3 DiffuseRenderer::randomUnitVec3() {
	double phi = PI2 * rand() / RAND_MAX;
	double cost = 1.0 * rand() / RAND_MAX;
	double sint = sqrt(1 - cost*cost);
	double x = sint * cos(phi);
	double y = sint * sin(phi);
	return Vec3(x, y, cost);
}

Color DiffuseRenderer::getObjectColor(Scene &scene, Ray &ray, double &t, Object* object) {
	Point3 hitPoint = ray.at(t);
	Vec3 n = object->getNormal(hitPoint);
	n.normalize();
	Color finalColor(0, 0, 0);
	for (int i = 0; i < scene.lights.size(); i++) {
		Vec3 dir = -scene.lights[i]->getDirection(hitPoint);
		finalColor += scene.lights[i]->diffuseColor(object->material, n, dir);
	}
	return finalColor;
}
