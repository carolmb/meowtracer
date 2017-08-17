#ifndef __CAMERA__
#define __CAMERA__

#include "Ray.h"

class Camera {
protected:
	Point3 position;
	Vec3 horizontal;
	Vec3 vertical;

	Camera() : horizontal(Vec3(1, 0, 0)), vertical(Vec3(0, 1, 0)), position(Vec3(0, 0, 0)) {}
	Camera(Vec3 &h, Vec3 &v, Point3 &pos) : horizontal(h), vertical(v), position(pos) {}
public:
	virtual Ray getRay(double i, double j) = 0;
	virtual double getDepth(Point3 p) = 0;
};

#endif