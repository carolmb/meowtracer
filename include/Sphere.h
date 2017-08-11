#ifndef __SPHERE__
#define __SPHERE__

#include "Ray.h"

class Sphere {
private:
	Point3 center;
	double radius;
public:
	Sphere(Point3 p, double r) : center(p), radius(r) {}
	bool hits(Ray &ray);
};

#endif