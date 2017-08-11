#include "../include/Sphere.h"
#include <iostream>

bool Sphere::hits(Ray &ray) {
	Vec3 origd = ray.getOrigin() - center;
	Vec3 dir = ray.getDirection();
	double a = dir.dot(dir);
	double b = 2 * dir.dot(origd);
	double c = origd.dot(origd) - radius*radius;

	double delta = b * b - 4 * a * c;
	return delta >= 0;  
}