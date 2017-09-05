#ifndef __LIGHT__
#define __LIGHT__

#include "Vec3.h"
#include "Material.h"
#include <cmath>

class Light {
public:
	Color color;
	Light(Color &c) : color(c) {}

	Color diffuseColor (Material* material, Vec3 &n, Vec3 &l);
	Color specularColor(Material* material, Vec3 &n, Vec3 &l, Vec3 &v);
	Color ambientColor(Material* material);

	virtual Vec3 getDirection(Point3 &point) = 0;

};

#endif