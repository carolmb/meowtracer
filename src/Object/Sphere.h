#ifndef __SPHERE__
#define __SPHERE__

#include "Object.h"

class Sphere : public Object {
private:
	Point3 center;
	double radius;
  Matrix4 invt;
public:
	Sphere(Point3 p, double r) : center(p), radius(r) {}
	double hit(Ray &ray);
	Vec3 getNormal(Point3 &p);
  void preprocess();
};

#endif