#ifndef __SPHERE__
#define __SPHERE__

#include "util/Ray.h"

class Sphere {
private:
	Point3 center;
	double radius;
public:
	Sphere(Point3 p, double r) : center(p), radius(r) {}
	bool hits(Ray &ray) {
		double a = ray.getDirection().dot(ray.getDirection());
		double b = 2 * (ray.origin() - center).dot(ray.getDirection());

		Vec3 v = (ray.origin() - center);
		double c = v.dot(v) - radius*radius;

		double delta = b * b - 4 * a * c;
		return delta < 0;  
	}
};

#endif