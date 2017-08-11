#include "../include/Sphere.h"
#include <iostream>

bool Sphere::hits(Ray &ray) {
	Vec3 o = ray.getOrigin() - center;
	Vec3 d = ray.getDirection();
	double a = d.dot(d);
	double b = 2 * d.dot(o);
	double c = o.dot(o) - radius*radius;

	double delta = b * b - 4 * a * c;
	return delta >= 0;  
}