#include "Light.h"
#include <iostream>

Color Light::diffuseColor (LightHit &lh) {
  float r = Vec3::Dot(lh.lightDir, lh.rayHit.normal);
  if (r > 0) {
    float a = getIntensity(lh);
    if (a > 0) {
      Color &diff = lh.rayHit.object->material->diffuse;
      Color &tex = lh.rayHit.texture;
      return (tex * diff * color) * fmin(1.0, r * a);
    }
  }
  return Color(0, 0, 0);
}

Color Light::specularColor(LightHit &lh) {
  Vec3 half = lh.lightDir - lh.rayDir;
  half = Vec3::Normalize(half);
  float r = Vec3::Dot(half, lh.rayHit.normal);
  if (r > 0) {
    float a = getIntensity(lh);
    if (a > 0) {
      float s = lh.rayHit.object->material->shininess;
      Color &spec = lh.rayHit.object->material->specular;
      Color &tex = lh.rayHit.texture;
      return (tex * spec * color) * fmin(1.0, pow(r * a, s));
    }
  }
  return Color(0, 0, 0);
}