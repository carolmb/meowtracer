#ifndef __SPHERE__
#define __SPHERE__

#include "Ray.h"

class Sphere {
private:
	Point3 center;
	double radius;
public:
	Sphere(Point3 p, double r) : center(p), radius(r) {}
	bool hits(Ray &ray) {
		Vec3 origd = ray.getOrigin() - center;
		Vec3 dir = ray.getDirection();
		double a = dir.dot(dir);
		double b = 2 * dir.dot(origd);
		double c = origd.dot(origd) - radius*radius;

		double delta = b * b - 4 * a * c;
		return delta < 0;  
	}
};

#endif