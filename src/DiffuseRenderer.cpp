#include "../include/DiffuseRenderer.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
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
			color *= hitObject->material->getColor();
			if (depth >= rayCount) {
				break;
			} else {
				Vec3 n = hitObject->getNormal(ray, mint);
				Point3 o = ray.at(mint);
				ray = Ray(o, n + randomUnitVec3());
			}
		} else {
			color *= scene.backgroundColor(x, y);
			break;
		}
	}
	return color;
}
