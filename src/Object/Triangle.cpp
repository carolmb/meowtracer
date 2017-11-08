#include "Triangle.h"
#include <iostream>
#include <cmath>

Triangle::Triangle(Matrix4 xform, Point3 &p0, Point3 &p1, Point3 &p2) {
  p0 = p0 * xform;
  p1 = p1 * xform;
  p2 = p2 * xform;

  Vec3 u = p1 - p0;
  Vec3 v = p2 - p0;
  Vec3 w;

  double uv = Vec3::Dot(u, v);
  double uu = Vec3::Dot(u, u);
  double vv = Vec3::Dot(v, v);
  double wu = Vec3::Dot(w, u);
  double wv = Vec3::Dot(w, v);
}

HitRecord Triangle::hit(Ray &ray) {
  HitRecord hr;




  Vec3 o = ray.getOrigin();
  Vec3 d = ray.getDirection();
  o = o * invt;
  d = d * invt;

  double a = Vec3::Dot(d, d);
  double b = 2 * Vec3::Dot(d, o);
  double c = Vec3::Dot(o, o) - 1;
  double delta = b * b - 4 * a * c;

  if (delta >= 0) {
    Ray tray = Ray(o, d);
    double sqrtdelta = std::sqrt(delta);
    double t1 = (-b - sqrtdelta) / (2 * a);
    double t2 = (-b + sqrtdelta) / (2 * a);
    hr.t = std::min(t1, t2);
    hr.point = ray.at(hr.t);
    hr.normal = tray.at(hr.t);
    hr.normal = hr.normal * transform;
    hr.normal = Vec3::Normalize(hr.normal);
  } else {
    hr.t = NAN;
  }
  return hr;
}