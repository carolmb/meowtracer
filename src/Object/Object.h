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
  Texture* texture = 0;
  virtual RayHit hit(Ray &ray) = 0;
  virtual Color radiosity(Vec2& uv) = 0;
  virtual Vec2 texUV(Vec2& uv) = 0;
};

struct RayHit {

  float t;
  Point3 point;
  Vec3 normal;
  Vec2 uv;
  Object* object = 0;

  Color getTexture() {
  	if (object->texture) {
      Vec2 t = object->texUV(uv);
  		return object->texture->getColor(t.x, t.y, point);
  	} else {
  		return Vec3(1, 1, 1);
  	}
  }

};

#endif