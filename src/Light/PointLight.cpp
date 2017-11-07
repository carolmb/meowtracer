#include "PointLight.h"

Vec3 PointLight::getDirection(Point3 &p) {
  return origin - p;
}