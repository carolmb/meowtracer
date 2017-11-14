#include "Triangle.h"
#include <iostream>
#include <cmath>
#define E 0.0000001

Triangle::Triangle(Matrix4 xform, Point3 &p0, Point3 &p1, Point3 &p2, bool c) {
  culling = c;
  p0 = xform.TransformPoint(p0);
  p1 = xform.TransformPoint(p1);
  p2 = xform.TransformPoint(p2);

  e0 = p1 - p0;
  e1 = p2 - p0;
  origin = p0;
  normal = Vec3::Cross(e0, e1);
}

HitRecord Triangle::hit(Ray &ray) {
  HitRecord hr;
  hr.t = NAN;

  Vec3 pvec = Vec3::Cross(ray.direction, e1);
  float det = Vec3::Dot(e0, pvec);

  if (culling) {
    if (det < E)
      return hr;
    Vec3 tvec = ray.origin - origin;
    float u = Vec3::Dot(tvec, pvec);
    if (u < 0 || u > det)
      return hr;
    Vec3 qvec = Vec3::Cross(tvec, e0);
    float v = Vec3::Dot(ray.direction, qvec);
    if (v < 0 || u + v > det)
      return hr;
    hr.t = Vec3::Dot(e1, qvec) / det;
  } else {
    if (det > -E && det < E)
      return hr;

    float inv_det = 1.0 / det;
    Vec3 tvec = ray.origin - origin;
    float u = Vec3::Dot(tvec, pvec) * inv_det;
    if (u < 0 || u > 1)
      return hr;

    Vec3 qvec = Vec3::Cross(tvec, e0);
    float v = Vec3::Dot(ray.direction, qvec) * inv_det;
    if (v < 0 || u + v > 1)
      return hr;
    hr.t = Vec3::Dot(e1, qvec) * inv_det;
  }
  hr.normal = normal;
  return hr;
}