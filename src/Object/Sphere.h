#ifndef __SPHERE__
#define __SPHERE__

#include "Object.h"

class Sphere : public Object {
private:
	Point3 center;
	float radius;
  Matrix4 invt;
public:
	Sphere(Matrix4 &xform, Point3 p, float r);
	HitRecord hit(Ray &ray);
};

#endif