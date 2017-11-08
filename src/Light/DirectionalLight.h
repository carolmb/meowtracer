#ifndef __DLIGHT__
#define __DLIGHT__

#include "Light.h"

class DirectionalLight : public Light {
private:
	Vec3 direction;
public:
	DirectionalLight(Matrix4 &xform, Color &c, Vec3 &dir) : 
    Light(c), direction(-xform.TransformVector(dir)) {}
	Vec3 getDirection(Point3 &p);
};

#endif