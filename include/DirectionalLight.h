#ifndef __DLIGHT__
#define __DLIGHT__

#include "Light.h"

class DirectionalLight : public Light {
private:
	Vec3 direction;
public:
	DirectionalLight(Color &c, Vec3 &dir) : Light(c), direction(dir) {}
	Vec3 getDirection(Point3 &p);
};

#endif