#ifndef __CAMERA__
#define __CAMERA__

#include "Ray.h"

class Camera {
protected:
	Camera() : horizontal(Vec3(1, 0, 0)), vertical(Vec3(0, 1, 0)), position(Vec3(0, 0, 0)) {}
	Camera(Vec3 &h, Vec3 &v, Point3 &pos) : horizontal(h), vertical(v), position(pos) {}
	Point3 position;
	Vec3 horizontal;
	Vec3 vertical;
public:
	Ray getRay(double i, double j) { return Ray(position + horizontal * i + vertical * j, getRayDirection(i, j)); }
	Vec3 getRayDirection(double i, double j);
};

#endif