#ifndef __SPHERE__
#define __SPHERE__

#include "Object.h"

class Sphere : public Object {
private:
  Matrix4 invt;
  Matrix4 transform;
  Point3 center;
  float radius;
public:
	Sphere(Matrix4 &xform, Point3 p, float r);
	RayHit hit(Ray &ray);
};

#endif