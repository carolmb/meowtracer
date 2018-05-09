#ifndef __OBJECT__
#define __OBJECT__

#include "../Math/Ray.h"
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"
#include "../Math/Matrix4.h"
#include "Material.h"
#include "Texture.h"

struct RayHit;

class Object {
public:
  Vec3 bounds[2];
  Material* material;
  Texture* texture;
  virtual RayHit hit(Ray &ray) = 0;
};

struct RayHit {
  float t;
  Point3 point;
  Vec3 normal;
  Vec2 uv;
  Object* object = 0;
  Color getTexture() {
  	if (object->texture) {
  		return object->texture->getColor(uv.x, uv.y, point);
  	} else {
  		return Vec3(1, 1, 1);
  	}
  }
};

#endif