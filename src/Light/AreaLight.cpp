#include "AreaLight.h"
#include "../Renderer/RendererUtil.h"

Vec3 AreaLight::getDirection(LightHit &lh) {
  Vec3 v = origin - lh.rayHit.point;
  v += randomUnitVec3(size);
  return v;
}