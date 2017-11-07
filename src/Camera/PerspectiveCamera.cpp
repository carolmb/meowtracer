#include "PerspectiveCamera.h"

Ray PerspectiveCamera::getRay(float i, float j) { 
	return Ray(lens, pixelPosition(i, j) - lens); 
}

float PerspectiveCamera::getDepth(Point3 p) {
	return (p - lens).Length();
}