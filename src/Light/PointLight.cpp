#include "PointLight.h"

Vec3 PointLight::getDirection(Point3 &point, Vec3 &normal, Vec3 &ray) {
  Vec3 dir = origin - point;
  dir.normalize();
  return dir;
}

Color PointLight::getColor(Point3 &point, Vec3 &normal, Vec3 &ray, Vec3 &light) {
  return color;
}