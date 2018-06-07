#include "RendererUtil.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

Vec2 randomVec2() {
  return Vec2(rand() / RAND_MAX, rand() / RAND_MAX);
}

Vec3 randomUnitVec3(float radius) {
  float phi = PI2 * rand() / RAND_MAX;
  float cost = 1.0 * rand() / RAND_MAX;
  float sint = sqrt(1 - cost*cost);
  float x = sint * cos(phi);
  float y = sint * sin(phi);
  return Vec3(x * radius, y * radius, cost * radius);
}

Vec2 beckmanRandom(float m2) {
  float e1 = rand() / RAND_MAX;
  float e2 = rand() / RAND_MAX;
  float tetha = 1; // TODO
  float phi = PI2 * e2;
  return Vec2(tetha, phi);
}

bool hitsBox(Vec3 bounds[2], Ray &r) {
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
  /*
  if (tzmin > tmin) 
      tmin = tzmin; 
  if (tzmax < tmax) 
      tmax = tzmax; 
  */

  return true;
}

bool hitsBox(Vec3 b1[2], Vec3 b2[2]) {
  if (b1[1].x < b2[0].x || b2[1].x < b1[0].x)
    return false;
  if (b1[1].y < b2[0].y || b2[1].y < b1[0].y)
    return false;
  if (b1[1].z < b2[0].z || b2[1].z < b1[0].z)
    return false;
  return true;
}