#ifndef __OBJECT__
#define __OBJECT__

#include "../Math/Ray.h"
#include "../Math/Vec3.h"
#include "../Math/Matrix4.h"
#include "Material.h"

struct RayHit;

class Object {
public:
	Material* material;
  Vec3 bounds[2];
	virtual RayHit hit(Ray &ray) = 0;
};

struct RayHit {
  float t;
  Point3 point;
  Vec3 normal;
  Object* object = 0;
};

#endif