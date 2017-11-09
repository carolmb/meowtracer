#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "Object.h"

class Triangle : public Object {
private:
  Vec3 normal;
  Vec3 origin;
  Vec3 e0, e1;
  bool culling;
public:
  Triangle(Matrix4 xform, Point3 &p0, Point3 &p1, Point3 &p2, bool c = false);
  HitRecord hit(Ray &ray);
};

#endif