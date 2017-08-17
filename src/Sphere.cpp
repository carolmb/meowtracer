#include "../include/Sphere.h"
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

Color Sphere::getColor(Ray &ray, double t) {
	Point3 p = ray.at(t);
	Vec3 n = (p - center).norm();
	int r = (n.x + 1) / 2 * 255;
	int g = (n.y + 1) / 2 * 255;
	int b = (n.z + 1) / 2 * 255;
	return Color(r, g, b);
}