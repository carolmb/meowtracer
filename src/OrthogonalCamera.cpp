#include "../include/OrthogonalCamera.h"

Ray OrthogonalCamera::getRay(double i, double j) { 
	return Ray(horizontal * i + vertical * j, Vec3(0, 0, -1)); 
}

double OrthogonalCamera::getDepth(Point3 p) {
	return (position.z - p.z);
}