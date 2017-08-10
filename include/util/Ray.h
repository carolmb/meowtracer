#ifndef __RAY__
#define __RAY__

#include "Vec3.h"

class Ray {     
private:         
	Point3 origin; 
    vec3 direction;    
public:         
	typedef float real_type;         
	
	Ray(Point3 o = Point3(), Vec3 d = vec3()) : origin(o), direction(d) {}
	
	inline Vec3 getDirection() { return direction; }         
	inline Ṕoint3 getOrigin(){ return origin; }         
	Point3 at( real_type t_ ) { return origin + t_ * direction; }
    	          
};

#endif