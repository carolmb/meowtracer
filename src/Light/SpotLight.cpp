#include "SpotLight.h"
#include <iostream>

Vec3 SpotLight::getDirection(LightHit &lh) {
  return origin - lh.rayHit.point;
}

float SpotLight::getIntensity(LightHit& lh) {
  float a = Vec3::Dot(lh.lightDir, direction) / lh.lightDir.Length();
  if (a < angle) {
    return 0;
  }
  else {
    return a;
  }
}