#include "../include/DiffuseRenderer.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iostream>
#define INF std::numeric_limits<double>::infinity()
#define PI2 6.28318530718 

Vec3 randomUnitVec3() {
	double phi = PI2 * rand() / RAND_MAX; 
	double cost = 1.0 * rand() / RAND_MAX; 
	double sint = sqrt(1 - cost*cost);
	double x = sint * cos(phi);
    double y = sint * sin(phi);
    return Vec3(x, y, cost);
}

Color DiffuseRenderer::getColor(Scene &scene, Ray &ray, double &x, double &y) {
	int depth = 0;
	Object* hitObject;
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
		Color color = hitObject->material->getColor();
		Vec3 n = hitObject->getNormal(ray, mint);
		n.normalize();
		Color finalColor(0, 0, 0);
		for (int i = 0; i < scene.lights.size(); i++) {
			double r = (scene.lights[i].direction.dot(n));
			if (r > 0) {
				finalColor += (color * scene.lights[i].color) * r;
			}
		}
		return finalColor;
	} else {
		return scene.backgroundColor(x, y);
	}
}
