#ifndef __PLIGHT__
#define __PLIGHT__

#include "Light.h"

class PointLight : public Light {
private:
  Point3 origin;
public:
  PointLight(Color &c, Point3 &o) : Light(c), origin(o) {}
  Vec3 getDirection(Point3 &point, Vec3 &normal, Vec3 &ray);
  Color getColor(Point3 &point, Vec3 &normal, Vec3 &ray, Vec3 &light);
};

#endif