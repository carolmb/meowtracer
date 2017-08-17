#ifndef __SPHERE__
#define __SPHERE__

#include "Ray.h"
#include "Color.h"

class Sphere {
private:
	Point3 center;
	double radius;
public:
	Sphere(Point3 p, double r) : center(p), radius(r) {}
	double hit(Ray &ray);
	Color getColor(Ray &ray, double t);
	double getDepth(Ray &ray, double t, double maxDepth);
};

#endif