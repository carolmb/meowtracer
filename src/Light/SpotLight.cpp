#include "SpotLight.h"

Vec3 SpotLight::getDirection(Point3 &p) {
  return origin - p;
}

Color SpotLight::diffuseColor (Material* material, Vec3 &n, Vec3 &l) {
  float r = Vec3::Dot(l, n);
  if (r > 0) {
    Vec3 d = Vec3::Normalize(l);
    float a = Vec3::Dot(l, direction) / l.Length();
    if (a >= angle) {
      return (material->diffuse * color) * fmin(1.0, r * a);
    }
  }
  return Color(0, 0, 0);
}

Color SpotLight::specularColor(Material* material, Vec3 &n, Vec3 &l, Vec3 &v) {
  Vec3 half = l - v;
  half = Vec3::Normalize(half);
  float r = Vec3::Dot(half, n);
  if (r > 0) {
    float a = Vec3::Dot(l, direction) / l.Length();
    if (a >= angle) {
      return (material->specular * color) * fmin(1.0, pow(r * a, material->shininess));
    }
  }
  return Color(0, 0, 0);
}