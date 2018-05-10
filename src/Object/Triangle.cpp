#include "Triangle.h"
#include "../Renderer/RendererUtil.h"
#include <iostream>
#include <cmath>
#define E 0.0000000000001

float max3( float a, float b, float c ) {
  float max = ( a < b ) ? b : a;
  return ( ( max < c ) ? c : max );
}

float min3(float a, float b, float c) {
  float min = ( a > b ) ? b : a;
  return ( ( min > c ) ? c : min );
}

Triangle::Triangle(Matrix4 xform, Point3 &p0, Point3 &p1, Point3 &p2, bool c) {
  culling = c;
  p0 = xform.TransformPoint(p0);
  p1 = xform.TransformPoint(p1);
  p2 = xform.TransformPoint(p2);

  e1 = p1 - p0;
  e2 = p2 - p0;
  origin = p0;
  normals[0] = Vec3::Cross(e1, e2);
  normals[0] = Vec3::Normalize(normals[0]);
  normals[1] = normals[2] = normals[0];
  tex[0] = tex[1] = tex[2] = Vec2(0, 0);

  bounds[0] = Vec3(min3(p0.x, p1.x, p2.x), min3(p0.y, p1.y, p2.y), min3(p0.z, p1.z, p2.z));
  bounds[1] = Vec3(max3(p0.x, p1.x, p2.x), max3(p0.y, p1.y, p2.y), max3(p0.z, p1.z, p2.z));
}

void Triangle::setNormals(Vec3& n1, Vec3& n2, Vec3& n3)  {
  if (n1.Valid() && n2.Valid() && n3.Valid()) {
    normals[0] = n1; 
    normals[1] = n2; 
    normals[2] = n3;
  }
}

void Triangle::setTexUVs(Vec2& t1, Vec2& t2, Vec2& t3) {
  if (t1.Valid() && t2.Valid() && t3.Valid()) {
    tex[0] = t1; 
    tex[1] = t2; 
    tex[2] = t3;
  }
}

RayHit Triangle::hit(Ray &ray) {
  RayHit rh;
  rh.t = NAN;
  if (!hitsBox(bounds, ray)) {
    return rh;
  }

  Vec3 e2vec = Vec3::Cross(ray.direction, e2);
  float det = Vec3::Dot(e1, e2vec);

  float u, v;
  if (culling) {
    if (det < E)
      return rh;

    Vec3 tvec = ray.origin - origin;
    u = Vec3::Dot(tvec, e2vec);
    if (u < 0 || u > det)
      return rh;
    Vec3 e1vec = Vec3::Cross(tvec, e1);
    v = Vec3::Dot(ray.direction, e1vec);
    if (v < 0 || u + v > det)
      return rh;
    rh.t = Vec3::Dot(e2, e1vec) / det;

  } else {
    if (det > -E && det < E)
      return rh;

    float inv_det = 1.0 / det;
    Vec3 tvec = ray.origin - origin;
    u = Vec3::Dot(tvec, e2vec) * inv_det;
    if (u < 0 || u > 1)
      return rh;

    Vec3 e1vec = Vec3::Cross(tvec, e1);
    v = Vec3::Dot(ray.direction, e1vec) * inv_det;
    if (v < 0 || u + v > 1)
      return rh;
    rh.t = Vec3::Dot(e2, e1vec) * inv_det;

  }
  double w = 1 - u - v;
  rh.uv = tex[0] * w + tex[1] * u + tex[2] * v;
  rh.normal = normals[0] * w + normals[1] * u + normals[2] * v;
  rh.normal.Print();
  std::cout << std::endl;
  return rh;
}