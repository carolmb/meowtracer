#ifndef __OBJECT__
#define __OBJECT__

#include "Ray.h"
#include "Vec3.h"

class Object {
public:
	virtual double hit(Ray &ray) = 0;
	virtual Color getColor(Ray &ray, double t) = 0;
};

#endif