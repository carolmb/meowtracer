#ifndef __SLIGHT__
#define __SLIGHT__

#include "Light.h"

class SpotLight : public Light {
private:
  Point3 origin;
  Vec3 direction;
  double angle;
public:
  SpotLight(Color &c, Point3 &o, Vec3 d, double a) : Light(c), origin(o), direction(-d), angle(a) {
    direction.normalize();
  }
  Vec3 getDirection(Point3 &point, Vec3 &normal, Vec3 &ray);
  Color getColor(Point3 &point, Vec3 &normal, Vec3 &ray, Vec3 &light);
};

#endif