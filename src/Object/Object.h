#ifndef __OBJECT__
#define __OBJECT__

#include "../Math/Ray.h"
#include "../Math/Vec3.h"
#include "../Math/Matrix4.h"
#include "Material.h"

struct HitRecord {
  double t;
  Point3 point;
  Vec3 normal;
};

class Object {
public:
  Matrix4 transform;
	Material* material;
	virtual HitRecord hit(Ray &ray) = 0;
};

#endif