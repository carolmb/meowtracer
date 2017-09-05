#ifndef __ALIGHT__
#define __ALIGHT__

#include "Light.h"

class AmbientLight : public Light {
public:
	AmbientLight(Color &c) : Light(c) {}
	double getIntensity(Vec3 &n);
};

#endif