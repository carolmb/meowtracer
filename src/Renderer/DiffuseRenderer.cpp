#include "DiffuseRenderer.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iostream>
#define INF std::numeric_limits<float>::infinity()
#define PI2 6.28318530718 

Color DiffuseRenderer::getColor(Scene &scene, Ray &initRay, float &x, float &y) {
	int depth = 0;
	Object* hitObject;
	Ray ray = initRay;
	Color color(1, 1, 1);
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
			color = color * getObjectColor(scene, ray, minhr, hitObject);
			if (depth >= rayCount) {
				break;
			} else {
				Point3 d = minhr.normal + randomUnitVec3();
				ray = Ray(minhr.point, d);
			}
		} else {
			color = color * scene.backgroundColor(x, y);
			break;
		}
	}
	return color;
}

Vec3 DiffuseRenderer::randomUnitVec3() {
	float phi = PI2 * rand() / RAND_MAX;
	float cost = 1.0 * rand() / RAND_MAX;
	float sint = sqrt(1 - cost*cost);
	float x = sint * cos(phi);
	float y = sint * sin(phi);
	return Vec3(x, y, cost);
}

Color DiffuseRenderer::getObjectColor(Scene &scene, Ray &ray, HitRecord &hr, Object* object) {
	Color finalColor(0, 0, 0);
	for (int i = 0; i < scene.lights.size(); i++) {
		Vec3 dir = -scene.lights[i]->getDirection(hr.point);
		finalColor += scene.lights[i]->diffuseColor(object->material, hr, dir);
	}
	return finalColor;
}
