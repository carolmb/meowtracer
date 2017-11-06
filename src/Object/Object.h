#ifndef __OBJECT__
#define __OBJECT__

#include "../Ray.h"
#include "../Vec3.h"
#include "../Transform.h"

class Object {
public:
	int materialID;
  Transform transform;
	virtual double hit(Ray &ray) = 0;
	virtual Vec3 getNormal(Point3 &p) = 0;
};

#endif