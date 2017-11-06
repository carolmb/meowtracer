#include "Sphere.h"
#include <iostream>
#include <cmath>

double Sphere::hit(Ray &ray) {
	Vec3 o = ray.getOrigin() - center;
	Vec3 d = ray.getDirection();
	double a = d.dot(d);
	double b = 2 * d.dot(o);
	double c = o.dot(o) - radius*radius;

	double delta = b * b - 4 * a * c;
	if (delta >= 0) {
		double sqrtdelta = std::sqrt(delta);
		double t1 = (-b - sqrtdelta) / (2 * a);
		double t2 = (-b + sqrtdelta) / (2 * a);
		return std::min(t1, t2);
	} else {
		return NAN;
	}
}

Vec3 Sphere::getNormal(Point3 &p) {
	return (p - center).norm();
}