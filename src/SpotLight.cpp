#include "../include/SpotLight.h"

Vec3 SpotLight::getDirection(Point3 &p) {
  return origin - p;
}

Color SpotLight::diffuseColor (Material* material, Vec3 &n, Vec3 &l) {
  double r = l.dot(n);
  if (r > 0) {
    Vec3 d = -l;
    d.normalize();
    double a = (-l).dot(direction);
    if (a >= angle) {
      return (material->diffuse * color) * fmin(1.0, r * a);
    }
  }
  return Color(0, 0, 0);
}

Color SpotLight::specularColor(Material* material, Vec3 &n, Vec3 &l, Vec3 &v) {
  Vec3 half = l - v;
  half.normalize();
  double r = half.dot(n);
  if (r > 0) {
    l.normalize();
    double a = (-l).dot(direction);
    if (a >= angle) {
      return (material->specular * color) * fmin(1.0, pow(r * a, material->shininess));
    }
  }
  return Color(0, 0, 0);
}