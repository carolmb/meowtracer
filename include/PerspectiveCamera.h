
#ifndef __PRSCAMERA__
#define __PRSCAMERA__

#include "Camera.h"

class PerspectiveCamera : public Camera {
protected:
	Point3 lens;
	Vec3 getRayDirection(double i, double j);
public:
	PerspectiveCamera() : Camera(), lens(Point3(0.5, 0.5, 1)) {}
	PerspectiveCamera(Point3& l) : Camera(), lens(l) {}
	PerspectiveCamera(Vec3 &h, Vec3 &v, Point3 &pos, Point3 &l) :  Camera(h, v, pos), lens(l) {}
};

#endif