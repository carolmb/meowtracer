#ifndef __LIGHT__
#define __LIGHT__

#include "../Math/Vec3.h"
#include "../Object/Object.h"
#include <cmath>

class Light {
public:
	Color color;
	Light(Color &c) : color(c) {}

	virtual Color diffuseColor (Material* material, HitRecord &hr, Vec3 &l);
	virtual Color specularColor(Material* material, HitRecord &hr, Vec3 &l, Vec3 &v);

	virtual Vec3 getDirection(Point3 &point) = 0;

};

#endif