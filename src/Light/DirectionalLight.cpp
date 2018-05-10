#include "DirectionalLight.h"

LightHit DirectionalLight::getHit(Vec3& rd, RayHit& rh) {
	LightHit lh(rd, rh);
	lh.lightDir = direction;
	return lh;
}