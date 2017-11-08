#ifndef __RAY__
#define __RAY__

#include "Vec3.h"

class Ray {     
public:        
  Point3 origin; 
  Vec3 direction;
	Ray(Point3 o = Point3(), Vec3 d = Vec3()) : origin(o), direction(d) {}
	Point3 at(float n) { return origin + direction * n; }
	void normalize() { direction = direction * (1 / direction.Length()); }
};

#endif