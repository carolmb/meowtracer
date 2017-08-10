#ifndef __ORTCAMERA__
#define __ORTCAMERA__

#include "Camera.h"

class OrthogonalCamera : public Camera {
public:
	OrthogonalCamera() : Camera() {}
	OrthogonalCamera(Vec3 &h, Vec3 &v, Point3 &pos) : Camera(h, v, pos) {}
	Vec3 getRayDirection(double i, double j) { return horizontal + vertical; }
};

#endif