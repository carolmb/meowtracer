
#ifndef __PRSCAMERA__
#define __PRSCAMERA__

#include "../../include/util/Camera.h"

class PerspectiveCamera : public Camera {
private:
	Point3 lens;
public:
	OrthogonalCamera() : horizontal(Vec3(1, 0, 0)), vertical(Vec3(0, 1, 0)), position(Vec3(0, 0, 0)), lens(Vec3(0, 0, 1)) {}
	PerspectiveCamera(Vec3 &h, Vec3 &v, Point3 &pos, Point3 $l) : horizontal(h), vertical(v), position(pos), lens(l) {}
	Vec3 getRayDirection(double i, double j) { return lens + horizontal * i + vertical * j; }
};

#endif