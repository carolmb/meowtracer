#ifndef __ORTCAMERA__
#define __ORTCAMERA__

#include "Camera.h"

class OrthogonalCamera : public Camera {
protected:
	Vec3 getRayDirection(float i, float j);
public:
	OrthogonalCamera() : Camera() {}
	OrthogonalCamera(Vec3 &h, Vec3 &v, Point3 &pos) : Camera(h, v, pos) {}
	Ray getRay(float i, float j);
	float getDepth(Point3 p);
};

#endif