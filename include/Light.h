#ifndef __LIGHT__
#define __LIGHT__

#include "Vec3.h"

class Light {
public:
	Color color;
	Light(Color &c) : color(c) {}
	virtual double getIntensity(Vec3 &n) = 0;
};

#endif