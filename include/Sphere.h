#ifndef __SPHERE__
#define __SPHERE__

#include "Object.h"

class Sphere : public Object {
private:
	Point3 center;
	double radius;
public:
	Sphere(Point3 p, double r) : center(p), radius(r) {}
	double hit(Ray &ray);
	Vec3 getNormal(Point3 &p);
};

#endif