#ifndef __OBJECT__
#define __OBJECT__

#include "../Math/Ray.h"
#include "../Math/Vec3.h"
#include "../Math/Matrix4.h"
#include "Material.h"

struct HitRecord {
  float t;
  Point3 point;
  Vec3 normal;
};

class Object {
public:
	Material* material;
  Vec3 bounds[2];
	virtual HitRecord hit(Ray &ray) = 0;
  bool hitsBox(Ray &r) {

    float tmin, tmax, tymin, tymax, tzmin, tzmax; 
   
    tmin = (bounds[r.sign[0]].x - r.origin.x) * r.invdir.x; 
    tmax = (bounds[1-r.sign[0]].x - r.origin.x) * r.invdir.x; 
    tymin = (bounds[r.sign[1]].y - r.origin.y) * r.invdir.y; 
    tymax = (bounds[1-r.sign[1]].y - r.origin.y) * r.invdir.y; 

    if ((tmin > tymax) || (tymin > tmax)) 
        return false; 
    if (tymin > tmin) 
        tmin = tymin; 
    if (tymax < tmax) 
        tmax = tymax; 

    tzmin = (bounds[r.sign[2]].z - r.origin.z) * r.invdir.z; 
    tzmax = (bounds[1-r.sign[2]].z - r.origin.z) * r.invdir.z; 

    if ((tmin > tzmax) || (tzmin > tmax)) 
        return false; 
    if (tzmin > tmin) 
        tmin = tzmin; 
    if (tzmax < tmax) 
        tmax = tzmax; 

    return true;
  }
};

#endif