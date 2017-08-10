#ifndef __RAY__
#define __RAY__

#include "Vec3.h"

class Ray {     
private:         
	Point3 origin; 
    Vec3 direction;    
public:
	typedef double number;         
	Ray(Point3 o = Point3(), Vec3 d = Vec3()) : origin(o), direction(d) {}
	Vec3 getDirection() { return direction; }         
	Point3 getOrigin() { return origin; }         
	Point3 at(number n) { return origin + direction * n; }
};

#endif