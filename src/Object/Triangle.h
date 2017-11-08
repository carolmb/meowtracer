#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "Object.h"

class Triangle : public Object {
private:
  Vec3 normal;
public:
  Triangle(Matrix4 xform, Point3 &p0, Point3 &p1, Point3 &p2);
  HitRecord hit(Ray &ray);
};

#endif