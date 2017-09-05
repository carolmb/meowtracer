#ifndef __PLIGHT__
#define __PLIGHT__

#include "Light.h"

class ParallelLight : public Light {
private:
	Vec3 direction;
public:
	ParallelLight(Color &c, Vec3 &dir) : Light(c), direction(dir) {}
	double getIntensity(Vec3 &n);
};

#endif