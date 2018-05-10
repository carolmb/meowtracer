#ifndef __LIGHT__
#define __LIGHT__

#include "../Math/Vec3.h"
#include "../Object/Object.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<float>::infinity()

struct LightHit {
	RayHit& rayHit;
	Vec3& rayDir;
	Vec3 lightDir;
	float length = INF;
	LightHit(Vec3 &rd, RayHit &rh) : rayDir(rd), rayHit(rh) {}
};

class Light {
public:
	Color color;
	Light(Color &c) : color(c) {}

	virtual Color diffuseColor (LightHit &lh);
	virtual Color specularColor(LightHit &lh);
	virtual LightHit getHit(Vec3& rd, RayHit& rh) = 0;
	virtual float getIntensity(LightHit& lh) { return 1; }
};

#endif