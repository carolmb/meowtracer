#ifndef __RUTIL__
#define __RTUIL__

#include "../Scene.h"
#include "../Math/Vec3.h"
#include <limits>

#define INF std::numeric_limits<float>::infinity()
#define PI2 6.28318530718 

Vec3 randomUnitVec3(float radius = 1);
bool intersects(Scene &scene, Point3 &p, Vec3 &l);
bool hitsBox(Vec3 bounds[2], Ray &r);
bool hitsBox(Vec3 b1[2], Vec3 b2[2]);

#endif