#include "SpotLight.h"
#include <iostream>

Vec3 SpotLight::getDirection(LightHit &lh) {
  return origin - lh.rayHit.point;
}

float SpotLight::getIntensity(Vec3 &obj, Vec3 &light) {
  float a = Vec3::Dot(obj, light) / obj.Length() / light.Length();
  if (a < angle)
    return 0;
  else
    return a;
}