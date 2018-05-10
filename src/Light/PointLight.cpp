#include "PointLight.h"

LightHit PointLight::getHit(Vec3& rd, RayHit& rh) {
	LightHit lh(rd, rh);
	lh.lightDir = origin - lh.rayHit.point;
	lh.length = lh.lightDir.Length();
	lh.lightDir = Vec3::Normalize(lh.lightDir);
	return lh;
}