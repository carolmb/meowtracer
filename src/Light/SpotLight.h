#ifndef __SLIGHT__
#define __SLIGHT__

#include "Light.h"
#include "../Math/Matrix4.h"

class SpotLight : public Light {
private:
  Point3 origin;
  Vec3 direction;
  double angle;
public:
  SpotLight(Matrix4 &xform, Color &c, Point3 &o, Vec3 d, double a) : 
    Light(c), origin(xform.TransformPoint(o)), direction(-xform.TransformVector(d)), angle(a) {}
  Vec3 getDirection(Point3 &p);
  Color diffuseColor (Material* material, Vec3 &n, Vec3 &l);
  Color specularColor(Material* material, Vec3 &n, Vec3 &l, Vec3 &v);

};

#endif