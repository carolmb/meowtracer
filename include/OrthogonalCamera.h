#ifndef __ORTCAMERA__
#define __ORTCAMERA__

#include "Camera.h"

class OrthogonalCamera : public Camera {
protected:
	Vec3 getRayDirection(double i, double j);
public:
	OrthogonalCamera() : Camera() {}
	OrthogonalCamera(Vec3 &h, Vec3 &v, Point3 &pos) : Camera(h, v, pos) {}
	Ray getRay(double i, double j);
	double getDepth(Point3 p);
};

#endif