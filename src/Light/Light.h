#ifndef __LIGHT__
#define __LIGHT__

#include "../Vec3.h"
#include <cmath>

class Light {
public:
	Color color;
	Light(Color &c) : color(c) {}
  virtual Vec3 getDirection(Point3 &point, Vec3 &normal, Vec3 &ray) = 0;
  virtual Color getColor(Point3 &point, Vec3 &normal, Vec3 &ray, Vec3 &light) = 0;
};

#endif