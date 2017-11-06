#include "NormalRenderer.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<double>::infinity()

Color NormalRenderer::getColor(Ray &ray, double &x, double &y) {
	int depth = 0;
	Object* hitObject = 0;
	double mint = INF;
	for (int i = 0; i < objects.size(); i++) {
		double t = objects[i]->hit(ray);
		if (!isnan(t) && t < mint && t > 0) {
			mint = t;
			hitObject = objects[i];
		}
	}
	if (hitObject) {
		Point3 hitPoint = ray.at(mint);
		Vec3 n = hitObject->getNormal(hitPoint);
		double r = (n.x + 1) / 2;
		double g = (n.y + 1) / 2;
		double b = (n.z + 1) / 2;
		return Color(r, g, b);
	} else {
		return Color(0, 0, 0);
	}
}
