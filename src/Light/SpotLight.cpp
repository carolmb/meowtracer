#include "SpotLight.h"
#include <iostream>

LightHit SpotLight::getHit(Vec3& rd, RayHit& rh) {
	LightHit lh(rd, rh);
	lh.lightDir = origin - lh.rayHit.point;
	lh.length = lh.lightDir.Length();
	lh.lightDir = Vec3::Normalize(lh.lightDir);
	return lh;
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