#include "SpotLight.h"

Vec3 SpotLight::getDirection(Point3 &point, Vec3 &normal, Vec3 &ray) {
  return origin - point;
}

Color SpotLight::getColor(Point3 &point, Vec3 &normal, Vec3 &ray, Vec3 &light) {
  double r = light.dot(normal);
  if (r > 0) {
    double a = light.dot(direction) / light.len();
    if (a >= angle) {
      return color * fmin(1.0, r * a);
    }
  }
  return Color(0, 0, 0);
}