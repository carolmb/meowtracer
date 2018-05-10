#include "SphereLight.h"
#include "../Renderer/RendererUtil.h"

LightHit SphereLight::getHit(Vec3& rd, RayHit& rh) {
	LightHit lh(rd, rh);
	lh.lightDir = origin - lh.rayHit.point + randomUnitVec3(size);
	lh.length = lh.lightDir.Length();
	lh.lightDir = Vec3::Normalize(lh.lightDir);
	return lh;
}

float SphereLight::getIntensity(LightHit& lh) {
  float a = Vec3::Dot(lh.lightDir, direction);
  if (a < angle) {
    return 0;
  }
  else {
    return a;
  }
}