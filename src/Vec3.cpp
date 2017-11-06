#include "../include/Vec3.h"

double Vec3::dot(Vec3 &other) { return x * other.x + y * other.y + z * other.z; }

Vec3 Vec3::norm() { 
  double l = len();
  return Vec3(x/l, y/l, z/l); 
}

Vec3 Vec3::normalize() {
  double l = len();
  x /= l; y /= l; z /= l;
}

Vec3 Vec3::lerp(Vec3 &other, double t) { 
  double tt = 1 - t;
  return Vec3(other.x * t + x * tt, 
        other.y * t + y * tt, 
        other.z * t + z * tt); 
}

Vec3 Vec3::halfway(Vec3 &other) {
  Vec3 v = other + *this;
  v.normalize();
  return v;
}