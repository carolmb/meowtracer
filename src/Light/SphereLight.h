#ifndef __ALIGHT__
#define __ALIGHT__

#include "Light.h"

class SphereLight : public Light {
private:
  Point3 origin;
  Vec3 direction;
  float angle;
  float size;
public:
  SphereLight(Matrix4 &xform, Color &c, Point3 &o, Vec3 d, float a, float s) : 
    Light(c), origin(xform.TransformPoint(o)), direction(-xform.TransformVector(d)), angle(a), size(s) {}
  LightHit getHit(Vec3& rd, RayHit& rh);
  float getIntensity(LightHit& lh);
};

#endif