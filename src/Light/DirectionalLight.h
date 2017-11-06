#ifndef __DLIGHT__
#define __DLIGHT__

#include "Light.h"

class DirectionalLight : public Light {
private:
	Vec3 direction;
public:
	DirectionalLight(Color &c, Vec3 &dir) : Light(c), direction(-dir) {
    direction.normalize();
  }
  Vec3 getDirection(Point3 &point, Vec3 &normal, Vec3 &ray);
  Color getColor(Point3 &point, Vec3 &normal, Vec3 &ray, Vec3 &light);
};

#endif