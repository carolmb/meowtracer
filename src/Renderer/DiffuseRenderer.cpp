#include "DiffuseRenderer.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iostream>
#define INF std::numeric_limits<double>::infinity()
#define PI2 6.28318530718 

Color DiffuseRenderer::getColor(Ray &initRay, double &x, double &y) {
	int depth = 0;
	Object* hitObject;
	Ray ray = initRay;
	Color color(1, 1, 1);
	while (true) {
		hitObject = 0;
		double mint = INF;
		for (int i = 0; i < objects.size(); i++) {
			double t = objects[i]->hit(ray);
			if (!isnan(t) && t < mint && t > 0) {
				mint = t;
				hitObject = objects[i];
			}
		}
		if (hitObject) {
			color *= getObjectColor(ray, mint, hitObject);
			if (depth >= rayCount) {
				break;
			} else {
				Point3 hitPoint = ray.at(mint);
				Vec3 n = hitObject->getNormal(hitPoint);
				Point3 d = n + randomUnitVec3();
				ray = Ray(hitPoint, d);
			}
		} else {
			color *= backgroundColor(x, y);
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

Color DiffuseRenderer::getLightColor(Light* light, Point3 &hitPoint, 
    Vec3 &normal, Vec3 &rayDir, Vec3 &lightDir, Object* obj) {
	Color mat = materials[object->materialID];
	Vec3 dir = -light->getDirection(hitPoint, normal, ray.getDirection());
	Color color = scene.lights[i]->getColor(hitPoint, normal, ray.getDirection(), dir);
	return mat * color * diffuseCoef(normal, dir);
}

Color DiffuseRenderer::getAmbientColor(Object* obj) {
	return ambientLight;
}

double DiffuseRenderer::diffuseCoef(Vec3 &normal, Vec3 &light) {
	double r = light.dot(normal);
	if (r > 0) {
		return fmin(1.0, r);
	} else {
		return 0;
	}
}